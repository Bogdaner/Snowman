#include "stdafx.h"
#include "Object.h"



Object::Object(const sf::Vector2f& position, const sf::Vector2f& size)
	:position{ position }, size{ size }
{
	sprite.setSize(size);
	//sprite.setOrigin(size / 2.0f);
	sprite.setPosition(position);
}

void Object::draw(sf::RenderTarget& window)
{
	window.draw(sprite);
}

Collider Object::get_collider()
{
	return Collider(sprite);
}