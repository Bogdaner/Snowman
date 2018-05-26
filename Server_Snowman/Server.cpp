#include "stdafx.h"
#include "Server.h"

Server::Server() : exit{false}
{
	if (socket.bind(SERVER_PORT) != sf::Socket::Done)
		throw CantBind;
	//socket.setBlocking(false);
	std::cout << sf::IpAddress::getLocalAddress() << std::endl;
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
		return;//throw ReceiveError;

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
		case Requests::DISCONNECT:
			sf::Uint32 ID;
			packet >> ID;
			client_disconnect(ID);
			break;
		default:
			break;
		}
	}
}

void Server::send_all_data(const sf::Uint32 ID)
{
	while (active_threads[ID])
	{
		std::shared_lock<std::shared_mutex> lock(clients_mutex);
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		sf::Packet packet;
		load_all_data(packet);
		socket.send(packet, clients.at(ID).first, clients.at(ID).second);
	}
}


void Server::load_all_data(sf::Packet& packet) const
{
	sf::Uint32 size = data.size();
	if (size <= 0)
		return;
	packet << size;
	for (auto it = clients.begin(); it != clients.end(); it++)	//petla po wszystkich klientach
	{
		// ID = it->first
		// ip = it->second.first
		// port = it->second.second
		packet << sf::Uint32(it->first); // load ID	

		std::shared_lock<std::shared_mutex> lock(data_mutex);
		packet << *data.at(it->first);
	}
}

void Server::client_disconnect(const sf::Uint32 ID)
{
	active_threads[ID] = false;
	std::unique_lock<std::shared_mutex> lock(clients_mutex);


	threads[ID].join();
	threads.erase(ID);
	IDs--;

	active_threads.erase(ID);
	clients.erase(ID);
	data.erase(ID);
}


void Server::send_id(const unsigned short int port, const sf::IpAddress ip)
{
	clients[IDs] = std::make_pair(ip, port); // zapisanie klienta
	sf::Packet p;
	p << sf::Uint32(IDs);
	socket.send(p, ip, port);
	std::unique_lock<std::shared_mutex> lock(data_mutex);
	active_threads[IDs] = true;
	data[IDs] = std::make_unique<Character>(sf::Vector2f(400.0f, 300.0f), sf::Vector2f(50.0f, 50.0f)); // na razie tak z dupy wspolrzedne itp te same co w
	threads[IDs] = (std::thread(&Server::send_all_data, this, IDs));
	IDs++;
}


void Server::save_data(sf::Packet& packet)
{
	sf::Uint32 id;
	packet >> id;
	packet >> *data[id];
}

const short int Server::SERVER_PORT = 2000;

unsigned int Server::IDs = 0;

const std::string Server::CantBind = "Cant bind a socket with specified port";

const std::string Server::ReceiveError = "Error while receiving a packet";

std::shared_mutex Server::data_mutex;

std::shared_mutex Server::clients_mutex;