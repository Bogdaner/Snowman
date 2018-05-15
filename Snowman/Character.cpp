#include "stdafx.h"
#include "Character.h"

Character::Character (const sf::Vector2f& pos)
	:Object(pos)
{
	sprite.setSize(sf::Vector2f(100.0f, 100.0f));
	sprite.setTexture(nullptr);
}

void Character::draw (sf::RenderTarget& rt) const
{
	rt.draw(sprite); // <-- hmm.. tu nie wiem jak robimy wyœwietlanie ? bo mieliœmy coœ tego typu;
}

void Character::update(const float gravity, const float delta_time)
{
	set_velocity(direction);
	// tu jeszcze bd updateowaæ klatki;
	sprite.move(velocity * delta_time);
}

void Character::set_velocity (sf::Vector2f& dir)
{
	dir.x = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir.x = 1.0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir.x = -1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		// jump
	}
	velocity = dir * SPEED;
	// tu te¿ animacja bd siê zmieniaæ;
}

Collider Character::get_collider()
{
	return Collider(sprite);
}

const float Character::SPEED = 100.0f;