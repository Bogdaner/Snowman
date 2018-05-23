#include "stdafx.h"
#include "Server.h"

sf::Packet& operator << (sf::Packet& packet, const Character& character)
{
	return packet << character.sprite.getPosition().x << character.sprite.getPosition().y;
}


void operator >> (sf::Packet& packet, Character& character)
{
	sf::Vector2f pos;
	packet >> pos.x >> pos.y;
	character.sprite.setPosition(pos);
}


Server::Server()
{
	if (socket.bind(SERVER_PORT) != sf::Socket::Done)
		throw CantBind;
	//socket.setBlocking(false);
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

	sf::Uint8 request;
	if (packet >> request)
	{
		switch (request)
		{
		case Requests::ASK_FOR_ID:
			send_id(sender_port, sender_ip);
			break;
		case Requests::STORE_DATA:
			save_data(packet);
			break;
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
		socket.send(packet, it->second.first, it->second.second);
	}
}


sf::Packet Server::load_all_data() const
{
	sf::Packet packet;
	sf::Uint32 size = data.size();
	packet << size;
	for (auto it = clients.begin(); it != clients.end(); it++)	//petla po wszystkich klientach
	{
		// ID = it->first
		// ip = it->second.first
		// port = it->second.second

		packet << sf::Uint32(it->first); // load ID
		packet << *data.at(it->first); //TO DO overload operator << for character
	}
	return packet;
}


void Server::send_id(const unsigned short int port, const sf::IpAddress ip)
{
	clients[IDs] = std::make_pair(ip, port); // zapisanie klienta
	sf::Packet p;
	p << sf::Uint32(IDs);
	socket.send(p, ip, port);
	data[IDs] = std::make_unique<Character>(sf::Vector2f(400.0f, 300.0f), sf::Vector2f(50.0f, 50.0f)); // na razie tak z dupy wspolrzedne te z worlda
	IDs++;
}


void Server::save_data(sf::Packet& packet)
{
	sf::Uint32 id;
	packet >> id;
	packet >> *data[id]; // TO DO overload operator << for character 
}

const short int Server::SERVER_PORT = 2000;

unsigned int Server::IDs = 0;

const std::string Server::CantBind = "Cant bind a socket with specified port";

const std::string Server::ReceiveError = "Error while receiving a packet";