#include "stdafx.h"
#include "Character.h"

Character::Character (const sf::Vector2f& position, const sf::Vector2f& size)
	:Object(position, size)
{
	cur_animation = AnimationIndex::WalkingRight;
	animations[int (AnimationIndex::WalkingLeft)] = Animation (int (AnimationIndex::WalkingLeft));
	animations[int (AnimationIndex::WalkingRight)] = Animation (int (AnimationIndex::WalkingRight));
}

void Character::update(const float gravity, const float delta_time)
{
	set_velocity(direction);
	// tu jeszcze bd updateowaæ klatki;
	animations[int (cur_animation)].update (delta_time);
	if (velocity.x == 0)
		animations[int (cur_animation)].set_sprite (sprite, false);
	else
	{
		animations[int (cur_animation)].set_sprite (sprite, true);
	}
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
	if (direction.x > 0.0f)
		cur_animation = AnimationIndex::WalkingRight;
	else if (direction.x < 0.0f)
		cur_animation = AnimationIndex::WalkingLeft;

	// tu te¿ animacja bd siê zmieniaæ;
}

const float Character::SPEED = 100.0f;