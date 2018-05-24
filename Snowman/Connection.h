#pragma once
#include "Character.h"
#include "..\Server_Snowman\Requests.h"
#include "SFML/Network.hpp"

class Connection
{
public:
	Connection();
	sf::Uint32 ask_for_id();
	void send_data(Character* c, const sf::Uint32 ID);
	void receive_data(std::map<sf::Uint32, std::unique_ptr<Character>>& enemies, const sf::Uint32 ID);
private:
	sf::UdpSocket socket;
	sf::IpAddress server_ip;
	static const unsigned short int SERVER_PORT;
protected:
};


sf::Packet& operator << (sf::Packet& packet, const Character& character);

void operator >> (sf::Packet& packet, Character& character);
