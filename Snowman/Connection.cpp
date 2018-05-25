#include "stdafx.h"
#include "Connection.h"

Connection::Connection()
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

void Connection::send_data(Character* c, const sf::Uint32 ID)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(3));
	sf::Packet packet;
	packet << sf::Uint8(Requests::STORE_DATA);
	packet << ID;
	packet << *c;
	socket.send(packet, server_ip, SERVER_PORT);
}

void Connection::receive_data(std::map<sf::Uint32, std::unique_ptr<Character>>& enemies, const sf::Uint32 ID)
{
	sf::IpAddress sender_adress;
	unsigned short int sender_port;
	sf::Packet packet;
	if (socket.receive(packet, sender_adress, sender_port) != sf::Socket::Done)
		return; // Error

	sf::Uint32 size;
	if(!(packet >> size)) return;
	for (int i = 0; i < size; i++)
	{
		sf::Uint32 received_ID;
		packet >> received_ID;
		if (received_ID == ID)
		{
			int tmp;
			int count;
			packet >> tmp >> tmp >> tmp;
			packet >> count;
			if(count > 0)
				packet >> tmp >> tmp >> tmp >> tmp >> tmp;
			continue;
		}

		if (enemies.find(received_ID) == enemies.end())
			enemies[received_ID] = std::make_unique<Character>(sf::Vector2f(400.0f, 300.0f), sf::Vector2f(50.0f, 50.0f));// tutaj tez brakuje tworzenia nowego przeciwnika
		
		packet >> *enemies[received_ID];
	}
}

const unsigned short int Connection::SERVER_PORT = 2000;

sf::Packet& operator << (sf::Packet& packet, const Character& character)
{
	packet << character.sprite.getPosition().x << character.sprite.getPosition().y <<
		(int)character.cur_animation << character.snowballs.size();
	
	//for (auto it = character.snowballs.begin (); it != character.snowballs.end (); it++)
	//	packet << (*it)->id << (*it)->sprite.getPosition ().x << 
	//		(*it)->sprite.getPosition ().y << (*it)->velocity.x << (*it)->velocity.y << 
	//		(int)(*it)->delete_step << (*it)->time_of_death;
	std::cout << std::endl << character.snowballs_count << " " << character.snowballs.size () << " ";

	if (character.snowballs.size () > 0)
	{
		packet << character.snowballs.back ()->id << character.snowballs.back ()->sprite.getPosition ().x <<
			character.snowballs.back ()->sprite.getPosition ().y << character.snowballs.back ()->velocity.x << 
			character.snowballs.back ()->velocity.y;
		
		std::cout << character.snowballs.back ()->id << " " << character.snowballs.back ()->sprite.getPosition ().x << " " <<
			character.snowballs.back ()->sprite.getPosition ().y << " " << character.snowballs.back ()->velocity.x << " " <<
			character.snowballs.back ()->velocity.y << std::endl;
	}

	return packet;
}


void operator >> (sf::Packet& packet, Character& character)
{
	sf::Vector2f pos;
	int animation_dir;
	int number_of_snowballs;
	bool is_in_vector = false;
	int snowball_id;
	sf::Vector2f vel;

	packet >> pos.x >> pos.y;
	character.sprite.setPosition(pos);
	packet >> animation_dir;
	character.cur_animation = (Character::AnimationIndex)animation_dir;

	packet >> number_of_snowballs;
	if(number_of_snowballs > 0)
	{
		is_in_vector = false;
		packet >> snowball_id;
		packet >> pos.x >> pos.y;
		packet >> vel.x >> vel.y;

		//std::cout << number_of_snowballs << "       " << snowball_id << "   ===>   " << "   _____  " << character.snowballs.size () << std::endl;
		
			
		if ((character.snowballs.size() > 0 && snowball_id == character.snowballs.back()->id) || character.last_deleted_snowball == snowball_id)
			is_in_vector = true;
			//std::cout << snowball_id << "   ===>   " << snowball_count << "   _____  " << character.snowballs.size() << std::endl;


		if (!is_in_vector) {
			std::shared_ptr<Snowball> tmp = std::make_shared<Snowball> (sf::Vector2f (0.0f, 0.0f), sf::Vector2f (0.0f, 0.0f), sf::Vector2f (25.0f, 25.0f), 0);
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