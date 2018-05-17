#include "stdafx.h"
#include "Object.h"



Object::Object(const sf::Vector2f& position, const sf::Vector2f& size)
	:position{ position }, size{ size }
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

Collider Object::get_collider()
{
	return Collider(sprite);
}