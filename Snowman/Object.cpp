#include "stdafx.h"
#include "Object.h"

sf::Vector2f Object::get_position () const
{
	return position;
}

sf::Vector2f Object::get_size () const
{
	return size;
}

sf::Vector2f Object::get_velocity () const
{
	return velocity;
}

void Object::set_position (const sf::Vector2f pos)
{
	position = pos;
}

void Object::set_size (const sf::Vector2f siz)
{
	size = siz;
}

void Object::set_velocity (const sf::Vector2f vel)
{
	velocity = vel;
}