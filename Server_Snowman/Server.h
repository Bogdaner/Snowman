#pragma once

#include "SFML/Network.hpp"
#include "SFML/Graphics.hpp"
#include "Requests.h"
#include "Character.h"
#include <map>
#include <memory>

class Server
{
public:
	Server();
	~Server();
	void receive();
	void send_all_data();
private:
	sf::Packet load_all_data() const;
	std::map<sf::Uint32, std::unique_ptr<Character>> data; // state of the all players connected to the server
	std::map<sf::Uint32, std::pair<sf::IpAddress, unsigned short int>> clients; // store map<ID, <ip, port>>
	sf::UdpSocket socket;
	void send_id(const unsigned short int port, const sf::IpAddress ip);
	void save_data(sf::Packet& packet);
	static unsigned int IDs;
	static const short int SERVER_PORT;
	static const std::string CantBind;
	static const std::string ReceiveError;
protected:
};

