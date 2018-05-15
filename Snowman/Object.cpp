#include "stdafx.h"
#include "Object.h"

Object::Object (const sf::Vector2f& pos)
	:position {pos}
{

}

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

sf::Vector2f Object::get_direction () const
{
	return direction;
}

sf::RectangleShape Object::get_sprite () const
{
	return sprite;
}

void Object::set_position (const sf::Vector2f& pos)
{
	position = pos;
}

void Object::set_size (const sf::Vector2f& siz)
{
	size = siz;
}

void Object::set_velocity (const sf::Vector2f& vel)
{
	velocity = vel;
}

void Object::set_direction (const sf::Vector2f& dir)
{
	direction = dir;
}

void Object::set_sprite (const sf::RectangleShape& spr)
{
	sprite = spr;
}