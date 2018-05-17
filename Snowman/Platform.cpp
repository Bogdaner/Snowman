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

}
