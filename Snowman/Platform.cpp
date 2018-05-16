#include "stdafx.h"
#include "Platform.h"


Platform::Platform(const sf::Vector2f& position, const sf::Vector2f& size, sf::Vertex *tile) : Object{ position, size }, tile{tile}
{

}


Platform::~Platform()
{

}


void Platform::update(const float gravity, const float delta_time)
{
	tile[0].position = sprite.getPosition();
	tile[1].position = sf::Vector2f(sprite.getPosition().x + size.x, sprite.getPosition().y);
	tile[2].position = sprite.getPosition() + size;
	tile[3].position = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + size.y);
}
