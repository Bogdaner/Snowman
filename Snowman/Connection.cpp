#include "stdafx.h"
#include "Connection.h"


sf::Packet& operator << (sf::Packet& packet, const Character& character)
{
	return packet << character.get_center_position().x << character.get_center_position().y;
}


void operator >> (sf::Packet& packet, Character& character)
{
	sf::Vector2f pos;
	packet >> pos.x >> pos.y;
	character.sprite.setPosition(pos);
}


void Connection::send_data(Character* c)
{
	server_ip = sf::IpAddress::getLocalAddress();
	socket.bind(sf::Socket::AnyPort);
	socket.setBlocking(false);
	while (true)
	{
		sf::Packet packet;
		packet << *c;
		socket.send(packet, server_ip, server_port);
	}
}


void Connection::receive_data(Character& character)
{
	socket.bind(sf::Socket::AnyPort);
	socket.setBlocking(false);

	sf::IpAddress sender_adress;
	unsigned short int sender_port;
	sf::Packet packet;
	if (socket.receive(packet, sender_adress, sender_port) != sf::Socket::Done)
		return; // Error

	packet >> character;
}

const unsigned short int Connection::server_port = 2000;

sf::IpAddress Connection::server_ip;

sf::UdpSocket Connection::socket;
