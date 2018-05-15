#include "stdafx.h"
#include "Object.h"

float Object::gravity_value = 300.0f;

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

void Object::set_position (sf::Vector2f pos)
{
	position = pos;
}

void Object::set_size (sf::Vector2f siz)
{
	size = siz;
}

void Object::set_velocity (sf::Vector2f vel)
{
	velocity = vel;
}

void Object::gravity (float time)
{
	if (velocity.y < 1000)
		velocity.y += gravity_value * time;
}