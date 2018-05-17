#include "stdafx.h"
#include "World.h"


World::World() : window{ sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Game" }, delta_time{ 0.0f }, player(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(50.0f, 50.0f)), // na razie wspolrzedne gracza z dupy 
	camera{sf::Vector2f(0.0f, 0.0f), WINDOW_SIZE} // camera (plater position, screen size)
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
		if (delta_time > 1.0f / 20.0f)
			delta_time = 1.0f / 20.0f;

		//std::cout << 1.0f / delta_time << std::endl; // print fps

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		for (unsigned int i = 0; i < objects.size(); i++)
		{
			objects[i]->update(GRAVITY, delta_time);
		}

		Collider player_collider = player.get_collider();
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->get_collider().check_collision(player_collider, player.collison_dir, 1.0f))
				player.on_collision();
		}
		player.update(GRAVITY, delta_time);

		camera.setCenter(player.get_center_position());
		//camera.setCenter((int)player.get_center_position().x, (int)player.get_center_position().y); // to rozwiazuje bug mapy ale postac zaczyna latac xDD

		window.clear();
		window.setView(camera);
		window.draw(map);
		window.draw(player); // Te metody na razie tu tymczasowo potem sie ogarnie jakos razem wszystkie

		window.display();
	}
}

const sf::Vector2f World::WINDOW_SIZE(1280, 720);

const float World::GRAVITY = 981.0f;