#include "stdafx.h"
#include "Character.h"

Character::Character (const sf::Vector2f& pos)
	:Object(pos)
{
	// tu trzeba ustawiæ jakieœ sprajciki itp;
}

void Character::draw (sf::RenderTarget& rt) const
{
	rt.draw (sprite); // <-- hmm.. tu nie wiem jak robimy wyœwietlanie ? bo mieliœmy coœ tego typu;
}

void Character::update (const float& gravity, const float& time)
{
	position += velocity * time;
	// tu jeszcze bd updateowaæ klatki;
	sprite.setPosition (position);
}

void Character::set_direction (const sf::Vector2f& dir)
{
	velocity = dir * SPEED;
	// tu te¿ animacja bd siê zmieniaæ;
}

const float Character::SPEED = 100.0f;