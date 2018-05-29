#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Collider.h"

class Object : public sf::Drawable, public sf::Transformable
{
public:
	Object() = default;
	Object (const sf::Vector2f& position, const sf::Vector2f& size);
	virtual void update(const float gravity, const float delta_time) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	Collider collider;   // collider jako zmienna w obiekcie
	sf::RectangleShape sprite; // znowu na razie public albo juz zostanie public zobaczy sie ;s
	sf::Vector2f velocity;
private:

protected:
	sf::Vector2f direction;
	sf::Vector2f size;
	static const float SPEED;
};