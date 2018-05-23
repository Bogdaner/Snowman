#pragma once

#include "Requests.h"
#include "..\Snowman\Character.h"
#include "..\Snowman\Connection.h"
#include "SFML/Network.hpp"
#include <map>

class Server
{
public:
	Server();
	~Server();
	void receive();
	void send_all_data();
private:
	sf::Packet load_all_data() const;
	std::map<unsigned int, std::unique_ptr<Character>> data; // state of the all players connected to the server
	std::map<unsigned short int, std::pair<sf::IpAddress, int>> clients; // store map<port, <ip, id>>
	sf::UdpSocket socket;
	void send_id(const unsigned short int port, const sf::IpAddress ip);
	void save_data(sf::Packet& packet);
	static unsigned int IDs;
	static const short int SERVER_PORT;
	static const std::string CantBind;
	static const std::string ReceiveError;
protected:
};

