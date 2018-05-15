#pragma once
#include <SFML/Graphics.hpp>

class Object
{
protected:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f velocity;
	static float gravity_value;
public:
	sf::Vector2f get_position () const;
	sf::Vector2f get_size () const;
	sf::Vector2f get_velocity () const;
	void set_position (sf::Vector2f);
	void set_size (sf::Vector2f);
	void set_velocity (sf::Vector2f);
	void gravity (float);
	virtual void update (float) = 0;
	virtual void draw (sf::RenderTarget& const) const = 0;
};