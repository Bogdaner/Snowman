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
	Connection();
	~Connection();
	void send_data(const Character& character);
	void receive_data(Character& character);
private:
	sf::IpAddress server_ip;
	sf::UdpSocket socket;
	static const unsigned short int server_port;
	friend sf::Packet& operator << (sf::Packet& packet, const Character& character);
	friend void operator >> (sf::Packet& packet, Character& character);
protected:
};

