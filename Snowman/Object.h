#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Object
{
public:
	Object (const sf::Vector2f& position, const sf::Vector2f& size);

	virtual void update(const float gravity, const float delta_time) = 0;
	virtual void draw(sf::RenderTarget& window);
	Collider get_collider();
protected:
	sf::RectangleShape sprite;
	sf::Vector2f direction;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f velocity;
	static const float WEIGHT;
};