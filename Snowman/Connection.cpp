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
			packet >> tmp >> tmp;
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
	return packet << character.sprite.getPosition().x << character.sprite.getPosition().y;
}


void operator >> (sf::Packet& packet, Character& character)
{
	sf::Vector2f pos;
	packet >> pos.x >> pos.y;
	character.sprite.setPosition(pos);
}