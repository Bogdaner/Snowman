#include "stdafx.h"
#include "Character.h"
#include <iostream>

Character::Character (const sf::Vector2f& position, const sf::Vector2f& size)
	:Object(position, size)
{

}

void Character::update(const float gravity, const float delta_time)
{
	set_velocity(direction, gravity, delta_time);
	// tu jeszcze bd updateowaæ klatki;
	sprite.move(velocity * delta_time);
}

void Character::on_collision()
{
	if (collison_dir == CollisionDir::COLLISION_LEFT || collison_dir == CollisionDir::COLLISION_RIGHT)
		velocity.x = 0;
	if (collison_dir == CollisionDir::COLLISION_DOWN)
	{
		velocity.y = 0;
		can_jump = true;
	}
	else if (collison_dir == CollisionDir::COLLISION_UP && velocity.y < 0.0f)
		velocity.y = 0;
}

sf::Vector2f Character::get_center_position() const
{
	return sprite.getPosition();
}

void Character::set_velocity (sf::Vector2f& dir, const float gravity, const float delta_time)
{
	dir = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir.x = 1.0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir.x = -1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && can_jump)
	{
		velocity.y = -sqrtf(2.0f * gravity * JUMP_HEIGHT);
		can_jump = false;
	}
	if (collison_dir == CollisionDir::NO_COLLISION)
		can_jump = false;

	velocity.y += gravity * delta_time;
	std::cout << velocity.y << std::endl;
	velocity.x = dir.x * SPEED;
	// tu te¿ animacja bd siê zmieniaæ;
}

const float Character::SPEED = 170.0f;
const float Character::JUMP_HEIGHT = 250.0f;