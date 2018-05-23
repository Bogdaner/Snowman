#pragma once
#include "Character.h"
#include "SFML/Network.hpp"

struct Data
{
	sf::Vector2f position;
};

class Connection
{
public:
	static void send_data(Character* c);
	static void receive_data(Character& c);
private:
	static sf::UdpSocket socket;
	static sf::IpAddress server_ip;
	static const unsigned short int server_port;

	friend sf::Packet& operator << (sf::Packet& packet, const Character& character);
	friend void operator >> (sf::Packet& packet, Character& character);
protected:
};

