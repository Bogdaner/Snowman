#pragma once
#include "SFML/Graphics.hpp"
#include "Character.h"
#include "TileMap.h"
#include "Snowball.h"
#include "Connection.h"
#include <iostream>
#include <thread>
#include <map>

class World
{
public:
	World();
	~World();
	void start();
private:
	enum game_stage {
		victory,
		defeat
	};
	void game_end (game_stage gs);
	void enemy_loop ();
	void player_loop ();
	void update_enemies(sf::Packet packet);
	std::map<sf::Uint32, std::unique_ptr<Character>> enemies;
	sf::Uint32 ID;
	Connection connection;
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock clock;
	sf::View camera;
	Character player;
	TileMap map;
	float delta_time;
	static const sf::Vector2f WINDOW_SIZE;
	static const float GRAVITY;
protected:
};
