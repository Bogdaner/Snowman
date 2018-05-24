#pragma once
#include "SFML/Network.hpp"
#include "Requests.h"
#include "Character.h"
#include "Connection.h"
#include <map>
#include <memory>
#include <thread>
#include <mutex>

class Server
{
public:
	Server();
	~Server();
	void receive();
	void send_all_data(const sf::Uint32 ID);
private:
	void load_all_data(sf::Packet& packet) const;
	std::map<sf::Uint32, std::unique_ptr<Character>> data; // state of the all players connected to the server
	std::map<sf::Uint32, std::pair<sf::IpAddress, unsigned short int>> clients; // store map<ID, <ip, port>>
	std::vector<std::thread> threads;
	sf::UdpSocket socket;
	void send_id(const unsigned short int port, const sf::IpAddress ip);
	void save_data(sf::Packet& packet);
	static unsigned int IDs;
	static const short int SERVER_PORT;
	static const std::string CantBind;
	static const std::string ReceiveError;
	static std::mutex data_mutex;
protected:
};

