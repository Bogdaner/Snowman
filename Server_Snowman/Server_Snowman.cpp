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
	return 0;
}

