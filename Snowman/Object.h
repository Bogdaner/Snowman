#pragma once
#include <SFML/Graphics.hpp>

class Object
{
public:
	Object (const sf::Vector2f&);
	sf::Vector2f get_position() const;
	sf::Vector2f get_size() const;
	sf::Vector2f get_velocity() const;
	sf::Vector2f get_direction () const;
	sf::RectangleShape get_sprite () const;
	void set_position(const sf::Vector2f&);
	void set_size(const sf::Vector2f&);
	void set_velocity(const sf::Vector2f&);
	void set_direction (const sf::Vector2f&);
	void set_sprite (const sf::RectangleShape&);
	virtual void update(void (const float&),const float&) = 0;
	virtual void draw(sf::RenderTarget&) const = 0;
protected:
	sf::RectangleShape sprite;
	sf::Vector2f direction;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f velocity;
	static const float weight;
};