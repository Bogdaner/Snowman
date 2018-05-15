#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Object.h"

int main ()
{
	sf::RenderWindow window (sf::VideoMode (1280, 720), "Snowman The Game");

	while (window.isOpen ())
	{
		sf::Event event;
		while (window.pollEvent (event))
		{
			if (event.type == sf::Event::Closed)
				window.close ();
		}
		window.clear ();
		window.display ();
	}
	return 0;
}