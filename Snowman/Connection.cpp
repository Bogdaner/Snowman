#include "stdafx.h"
#include "Connection.h"

Connection::Connection() : exit{false}
{
	server_ip = sf::IpAddress::getLocalAddress();
	socket.bind(sf::Socket::AnyPort);
}


sf::Uint32 Connection::ask_for_id()
{
	sf::Packet packet;
	packet << sf::Uint8(Requests::ASK_FOR_ID);
	socket.send(packet, server_ip, SERVER_PORT);
	sf::Uint32 id;

	sf::IpAddress sender_adress;
	unsigned short int sender_port;
	if (socket.receive(packet, sender_adress, sender_port) != sf::Socket::Done)
	{
		socket.setBlocking(false);
		return -1; // Error
	}

	packet >> id;

	socket.setBlocking(false);
	return id;
}


void Connection::send_data(Character& c, const sf::Uint32 ID)
{
	sf::Packet packet;
	packet << sf::Uint8(Requests::STORE_DATA);
	packet << ID;
	packet << c;
	socket.send(packet, server_ip, SERVER_PORT);
}


sf::Packet Connection::get_last_packet()
{
	std::lock_guard<std::mutex> lock(stack_mutex);
	sf::Packet last = received_packets.top(); // get newest packet
	received_packets = std::stack<sf::Packet>(); // clear stack
	return last;
}


void Connection::receive_data()
{
	while (exit == false)
	{
		sf::IpAddress sender_adress;
		unsigned short int sender_port;
		sf::Packet packet;
		if (socket.receive(packet, sender_adress, sender_port) != sf::Socket::Done)
			continue; // Error

		std::lock_guard<std::mutex> lock(stack_mutex);
		received_packets.push(packet);
	}
}


bool Connection::is_queue_empty()
{
	return received_packets.empty();
}


const unsigned short int Connection::SERVER_PORT = 2000;

std::mutex Connection::stack_mutex;


// Functions for getting character info from packets etc. 
sf::Packet& operator << (sf::Packet& packet, const Character& character)
{
	packet << character.sprite.getPosition ().x << character.sprite.getPosition ().y <<
		(int)character.cur_animation << character.is_moving << 
		character.animations[(int)character.cur_animation].frame << character.snowballs.size ();

	if (character.snowballs.size () > 0)
		packet << character.snowballs.back ()->id << character.snowballs.back ()->sprite.getPosition ().x <<
			character.snowballs.back ()->sprite.getPosition ().y << character.snowballs.back ()->velocity.x <<
			character.snowballs.back ()->velocity.y;

	return packet;
}


void operator >> (sf::Packet& packet, Character& character)
{
	sf::Vector2f pos;
	int animation_dir;
	int snowball_id;
	int number_of_snowballs;
	bool is_in_vector = false;
	bool is_moving;
	int frame;
	sf::Vector2f vel;

	packet >> pos.x >> pos.y;
	character.sprite.setPosition (pos);
	packet >> animation_dir;
	if (animation_dir > 1)		// temporary condition 4 testing 
		animation_dir = 1;		// cuz not workin perfect jet
	character.cur_animation = (Character::AnimationIndex)animation_dir;
	packet >> is_moving >> frame;
	character.is_moving = is_moving;
	character.animations[(int)character.cur_animation].frame = frame;

	packet >> number_of_snowballs;
	if (number_of_snowballs > 0)
	{
		is_in_vector = false;
		packet >> snowball_id;
		packet >> pos.x >> pos.y;
		packet >> vel.x >> vel.y;

		if ((character.snowballs.size () > 0 && 
			snowball_id == character.snowballs.back ()->id) || 
			character.last_deleted_snowball == snowball_id)
				is_in_vector = true;
		
		if (!is_in_vector) {
			std::shared_ptr<Snowball> tmp = std::make_shared<Snowball> (sf::Vector2f (0.0f, 0.0f), sf::Vector2f (0.0f, 0.0f), sf::Vector2f (25.0f, 25.0f));
			tmp->id = snowball_id;
			tmp->sprite.setPosition (pos);
			tmp->velocity = vel;
			character.snowballs.push_back (tmp);

			/*character.snowballs.push_back (std::unique_ptr<Snowball> (new Snowball ({ 0.0f,0.0f },
			{ 0.0f,0.0f }, { 25.0f,25.0f }, 0)));
			character.snowballs.at (character.snowballs.size () - 1)->id = snowball_id;
			character.snowballs.at (character.snowballs.size () - 1)->setPosition (pos);
			character.snowballs.at (character.snowballs.size () - 1)->velocity = vel;*/
		}

	}
}