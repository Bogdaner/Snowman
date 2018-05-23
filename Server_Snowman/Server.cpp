#include "stdafx.h"
#include "Server.h"


Server::Server()
{
	if (socket.bind(SERVER_PORT) != sf::Socket::Done)
		throw CantBind;

}


Server::~Server()
{

}


void Server::receive()
{
	sf::Packet packet;
	sf::IpAddress sender_ip;
	unsigned short sender_port;
	if (socket.receive(packet, sender_ip, sender_port) != sf::Socket::Done)
		throw ReceiveError;

	int request;
	if (packet >> request)
	{
		switch (request)
		{
		case Requests::ASK_FOR_ID:
			send_id(sender_port, sender_ip);
		case Requests::STORE_DATA:
			save_data(packet);
		default:
			break;
		}
	}
}

void Server::send_all_data()
{
	sf::Packet packet = load_all_data();
	for (auto it = clients.begin(); it != clients.end(); it++)
	{
		socket.send(packet, it->second.first, it->first);
	}
}


sf::Packet Server::load_all_data() const
{
	sf::Packet packet;
	for (auto it = clients.begin(); it != clients.end(); it++)	//petla po wszystkich klientach
	{
		// port = it->first
		// ip = it->second.first
		// id = it->second.second

		packet << it->second.second;
		//packet << data[it->second.second]; TO DO overload operator << for character
	}
	return packet;
}


void Server::send_id(const unsigned short int port, const sf::IpAddress ip)
{
	clients[port] = std::make_pair(ip, IDs); // zapisanie klienta
	sf::Packet p;
	p << IDs;
	socket.send(p, ip, port);
	IDs++;
}


void Server::save_data(sf::Packet& packet)
{
	int id;
	packet >> id;
	//packet >> data[id]; // TO DO overload operator << for character 
}


const short int Server::SERVER_PORT = 2000;

unsigned int Server::IDs = 0;

const std::string Server::CantBind = "Cant bind a socket with specified port";

const std::string Server::ReceiveError = "Error while receiving a packet";