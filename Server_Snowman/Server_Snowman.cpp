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
	}
	//std::thread t1(&Server::receive, &s);
	//t1.join();
	//t2.join();

	return 0;
}

