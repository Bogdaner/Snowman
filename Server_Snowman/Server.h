#pragma once
#include "SFML/Network.hpp"
#include "Requests.h"
#include "SFML/Graphics/Font.hpp"
#include "../Snowman/Character.h"
#include "../Snowman/Connection.h"
#include <map>
#include <memory>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <atomic>

class Server
{
public:
	Server();
	~Server();
	void receive();
	void send_all_data(const sf::Uint32 ID);
	std::atomic<bool> exit;
private:
	void load_all_data(sf::Packet& packet) const;
	std::map<sf::Uint32, std::unique_ptr<Character>> data; // state of the all players connected to the server
	std::map<sf::Uint32, std::pair<sf::IpAddress, unsigned short int>> clients; // store map<ID, <ip, port>>
	void client_disconnect(const sf::Uint32 ID);
	std::map<sf::Uint32, std::atomic<bool>> active_threads;
	std::map<sf::Uint32, std::thread> threads;
	sf::UdpSocket socket;
	void send_id(const unsigned short int port, const sf::IpAddress ip);
	void save_data(sf::Packet& packet);
	static unsigned int IDs;
	static const short int SERVER_PORT;
	static const std::string CantBind;
	static const std::string ReceiveError;

	static std::shared_mutex data_mutex;
	static std::shared_mutex clients_mutex;
protected:
};

