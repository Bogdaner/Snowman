#include "stdafx.h"
#include "Server.h"
#include <iostream>
#include <thread>

int main()
{
	Server s;

	while (true)
	{
		s.receive();
		s.send_all_data();
	}
	//std::thread t1(&Server::receive, &s);
	//std::thread t2(&Server::send_all_data, &s);
	//t1.join();
	//t2.join();

	return 0;
}

