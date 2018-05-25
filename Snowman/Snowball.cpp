#include "stdafx.h"
#include "Snowball.h"


Snowball::Snowball (const sf::Vector2f& dir, const sf::Vector2f& position, const sf::Vector2f& size)
	:Object (position, size)
{
	id = count;
	count++;
	delete_step = delete_steps::no_collision;
	time_of_death = 0;
	direction = dir;
	velocity.y = dir.y * SPEED;
	velocity.x = dir.x * SPEED;
	texture.loadFromFile ("textures/snowball.png");
	sprite.setTexture (&texture);
}

void Snowball::update (const float gravity, const float delta_time)
{
	set_velocity (direction, gravity, delta_time);
	sprite.move (velocity * delta_time);
	if(delete_step == delete_steps::after_collision)
		time_of_death += delta_time;
	if (time_of_death > TIME_TO_ERASING)
		delete_step = delete_steps::to_del;
}

void Snowball::on_collision ()				// tu trzeba ogarn¹æ kolizjê chyba 
{											// chwilowo jest metoda z postaci xD
	texture.loadFromFile ("textures/expo.png");
	sprite.setTexture (&texture);
	delete_step = delete_steps::after_collision;
	if (collison_dir == CollisionDir::COLLISION_LEFT || collison_dir == CollisionDir::COLLISION_RIGHT)
		velocity.x = 0;
	if (collison_dir == CollisionDir::COLLISION_DOWN)
		velocity.y = 0;
	else if (collison_dir == CollisionDir::COLLISION_UP && velocity.y < 0.0f)
		velocity.y = 0;
}

void Snowball::set_velocity (sf::Vector2f& dir, const float gravity, const float delta_time)
{
	velocity.y += gravity * delta_time;
}

void Snowball::draw (sf::RenderTarget& target) const
{
	target.draw (sprite);
}

int Snowball::count = 0;
const float Snowball::TIME_TO_ERASING = 0.05f;