#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include <vector>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 700), "SFML!");
	TileMap map;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(map);
		window.display();
	}
	return 0;
}