#include "stdafx.h"
#include "Connection.h"


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


Connection::Connection()
{
	server_ip = sf::IpAddress::getLocalAddress();
	socket.bind(sf::Socket::AnyPort);
	//socket.setBlocking(false);
}

sf::Uint32 Connection::ask_for_id()
{
	sf::Packet packet;
	packet << sf::Uint8(Requests::ASK_FOR_ID);
	sf::Uint32 id = socket.send(packet, server_ip, SERVER_PORT);
	return id;
}

void Connection::send_data(Character* c, const sf::Uint32 ID)
{
	sf::Packet packet;
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
	packet >> size;
	for (int i = 0; i < size; i++)
	{
		sf::Uint32 received_ID;
		packet >> received_ID;
		if (received_ID == ID)
			continue;
		if (enemies.find(received_ID) == enemies.end())
			;// tutaj tez brakuje tworzenia nowego przeciwnika
		
		packet >> *enemies[received_ID];
	}
}

const unsigned short int Connection::SERVER_PORT = 2000;
