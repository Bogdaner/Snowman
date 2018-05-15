#pragma once
#include <SFML/Graphics.hpp>

class Object
{
public:
	sf::Vector2f get_position() const;
	sf::Vector2f get_size() const;
	sf::Vector2f get_velocity() const;
	void set_position(const sf::Vector2f);
	void set_size(const sf::Vector2f);
	void set_velocity(const sf::Vector2f);
	virtual void update(const float delta_time) = 0;
	virtual void draw(sf::RenderTarget& const) const = 0;
protected:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f velocity;
	static const float weight;
};