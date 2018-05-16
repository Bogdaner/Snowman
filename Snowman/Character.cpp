#include "stdafx.h"
#include "Character.h"

Character::Character (const sf::Vector2f& position, const sf::Vector2f& size)
	:Object(position, size)
{

}

void Character::update(const float gravity, const float delta_time)
{
	set_velocity(direction);
	// tu jeszcze bd updateowaæ klatki;
	sprite.move(velocity * delta_time);
}

void Character::set_velocity (sf::Vector2f& dir)
{
	dir = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir.x = 1.0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir.x = -1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir.y = -1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir.y = 1.0f;
	//{
	//	// jump
	//}
	velocity = dir * SPEED;
	// tu te¿ animacja bd siê zmieniaæ;
}

const float Character::SPEED = 100.0f;