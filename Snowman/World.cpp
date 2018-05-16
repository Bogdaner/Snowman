#include "stdafx.h"
#include "World.h"

World::World() : window{ sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Game" }, delta_time{ 0.0f }, player(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(30.0f, 30.0f)) // na razie wspolrzedne gracza z dupy 
{
	for (auto platform : map.get_platforms())
		objects.push_back(std::unique_ptr<Platform>(new Platform(platform)));
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

		player.update(GRAVITY, delta_time);
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->update(GRAVITY, delta_time);
		}

		Collider player_collider = player.get_collider();
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->get_collider().check_collision(player_collider, player.collison_dir, 0.5f);
		}

		window.clear();
		window.draw(map);
		player.draw(window); // Te metody na razie tu tymczasowo potem sie ogarnie jakos razem wszystkie

		window.display();
	}
}

const sf::Vector2u World::WINDOW_SIZE(1280, 720);

const float World::GRAVITY = 9.81f;