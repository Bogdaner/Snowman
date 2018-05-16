#pragma once
#include "SFML/Graphics.hpp"
#include "Character.h"
#include "TileMap.h"

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
	Character player;
	TileMap map;
	std::vector<std::unique_ptr<Object>> objects;
	float delta_time;
	static const sf::Vector2u WINDOW_SIZE;
	static const float GRAVITY;
protected:
};
