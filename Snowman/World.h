#pragma once
#include "SFML/Graphics.hpp"
#include "Character.h"
#include "TileMap.h"
#include "Snowball.h"
#include <iostream>

class World
{
public:
	World();
	~World();
	void start();
private:
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock clock;
	sf::View camera;
	Character player;
	TileMap map;
	std::vector<std::unique_ptr<Object>> objects;
	float delta_time;
	static const sf::Vector2f WINDOW_SIZE;
	static const float GRAVITY;
protected:
};
