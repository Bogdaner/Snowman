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
	return packet << character.sprite.getPosition().x << character.sprite.getPosition().y;
}


void operator >> (sf::Packet& packet, Character& character)
{
	sf::Vector2f pos;
	packet >> pos.x >> pos.y;
	character.sprite.setPosition(pos);
}