#pragma once
#include "Character.h"
#include "..\Server_Snowman\Requests.h"
#include "SFML/Network.hpp"
#include <stack>
#include <atomic>
#include <mutex>

class Connection
{
public:
	Connection();
	sf::Uint32 ask_for_id();
	void send_data(Character& c, const sf::Uint32 ID);
	sf::Packet get_last_packet();
	static void load_snowballs (sf::Packet& packet, Character& character);
	static void load_character (sf::Packet& packet, Character& character);
	static void pack_snowballs (sf::Packet& packet, const Character& character);
	static void pack_character (sf::Packet& packet, const Character& character);
	std::atomic<bool> exit;
	void receive_data();
	bool is_queue_empty();
private:
	sf::UdpSocket socket;
	sf::IpAddress server_ip;
	std::stack<sf::Packet> received_packets;
	static const unsigned short int SERVER_PORT;
	static std::mutex stack_mutex;
protected:
};


sf::Packet& operator << (sf::Packet& packet, const Character& character);

void operator >> (sf::Packet& packet, Character& character);
