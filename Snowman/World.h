#pragma once
#include "SFML/Graphics.hpp"
#include "Character.h"

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
	float delta_time;
	static const sf::Vector2u WINDOW_SIZE;
	static const float GRAVITY;
protected:
};
