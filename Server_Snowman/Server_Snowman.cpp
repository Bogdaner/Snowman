#include "stdafx.h"
#include "SFML/Network.hpp"
#include <iostream>

int main()
{
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();

	sf::UdpSocket socket;
	std::map<unsigned short int, sf::IpAddress> clients;
	constexpr int server_port = 2000;

	if (socket.bind(server_port) != sf::Socket::Done)
		return -1; //some kind of error occurred

	socket.setBlocking(false); // jak tego sie nie ustawi to czeka az cos sie przesle 

	while (true)
	{	
		sf::Packet packet;
		sf::IpAddress sender_ip;
		unsigned short sender_port;
		if (socket.receive(packet, sender_ip, sender_port) != sf::Socket::Done)
		{
			// Error
		}
		sf::Vector2f character_position;
		if (packet >> character_position.x >> character_position.y)
		{
			clients[sender_port] = sender_ip; // zapisanie klienta
			std::cout << "X: " << character_position.x << " Y: " << character_position.y << std::endl;
		}
		else
			;// Error

		for (std::map<unsigned short int, sf::IpAddress>::iterator it = clients.begin(); it != clients.end(); it++)	//petla po wszystkich klientach
			socket.send(packet, it->second, it->first);
	}

	return 0;
}

