#include "stdafx.h"
#include "Object.h"



Object::Object(const sf::Vector2f& position, const sf::Vector2f& size)
	:size{ size }, collider{sprite}
{
	sprite.setSize(size);
	sprite.setOrigin(sprite.getSize() / 2.0f);
	sprite.setPosition(position);
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

const float Object::SPEED = 170.0f;