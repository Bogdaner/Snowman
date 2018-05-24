#include "stdafx.h"
#include "World.h"


World::World() : window{ sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Game" }, delta_time{ 0.0f }, player(sf::Vector2f(400.0f, 300.0f), sf::Vector2f(50.0f, 50.0f)), // na razie wspolrzedne gracza z dupy 
	camera{sf::Vector2f(0.0f, 0.0f), WINDOW_SIZE} // camera (player position, screen size)
{
	ID = connection.ask_for_id();
}

World::~World()
{

}

void World::start()
{
	while (window.isOpen())
	{
		connection.receive_data(enemies, ID);
		connection.send_data(&player, ID);

		delta_time = clock.restart().asSeconds();
		if (delta_time > 1.0f / 20.0f)
			delta_time = 1.0f / 20.0f;

		std::cout << 1.0f / delta_time << std::endl; // print fps
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();		
		}

		for (unsigned int i = 0; i < map.platforms.size(); i++)
		{
			map.platforms[i]->update(GRAVITY, delta_time);
		}	
		for (unsigned int i = 0; i < map.platforms.size(); i++)
		{
			if (map.platforms[i]->collider.check_collision(player.collider, player.collison_dir, 1.0f))
				player.on_collision();

			for (unsigned int j = 0; j < player.snowballs.size(); j++)			
				if (map.platforms[i]->collider.check_collision (player.snowballs[j]->collider, player.snowballs[j]->collison_dir, 1.0f)) {
					player.snowballs[j]->on_collision ();	// wykrywanie kolizji dla sniezek z platformami
															//player.snowballs.erase (player.snowballs.begin () + j);
				}
		}
		player.update(GRAVITY, delta_time);


		//camera.setCenter(player.get_center_position());
		camera.setCenter((int)player.get_center_position().x, (int)player.get_center_position().y); // to rozwiazuje bug mapy ale postac zaczyna latac xDD
		player.shooting (window);													// metoda ze strzelaniem dla postaci 
		for (unsigned int i = 0; i < player.snowballs.size (); i++) {				// update œnie¿ek
			player.snowballs[i]->update (GRAVITY, delta_time);
			if(player.snowballs[i]->delete_step == Snowball::delete_steps::to_del)
				player.snowballs.erase(player.snowballs.begin () + i);
		}			// mo¿na to pewnie ³adniej gdzieœ zrobic

		// Te metody na razie tu tymczasowo potem sie ogarnie jakos razem wszystkie
		window.clear();
		//Camera
		window.setView(camera);
		//Drawing
		window.draw(map);
		for (auto it = enemies.begin(); it != enemies.end(); it++)
			window.draw(*it->second);
		window.draw(player); 
		for (unsigned int i = 0; i < player.snowballs.size (); i++)				// nie mia³em pomys³u jak je rysowaæ xD
			player.snowballs[i]->draw (window);									// trzeba jeszcze dorobic kolizje dla sniezek

		window.display();
	}
}

const sf::Vector2f World::WINDOW_SIZE(1280, 720);

const float World::GRAVITY = 981.0f;