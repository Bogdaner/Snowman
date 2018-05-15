#include "stdafx.h"
#include "World.h"

World::World() : window{ sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Game" }, delta_time{ 0.0f }
{

}

World::~World()
{

}

void World::start()
{
	while (window.isOpen())
	{
		delta_time = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.display();
	}
}

const sf::Vector2u World::WINDOW_SIZE(1280, 720);

const float World::GRAVITY = 9.81f;