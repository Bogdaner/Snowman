#include "stdafx.h"
#include "Snowball.h"


Snowball::Snowball (const sf::Vector2f& dir, const sf::Vector2f& position, const sf::Vector2f& size)
	:Object (position, size)
{
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
}

void Snowball::on_collision ()				// tu trzeba ogarn�� kolizj� chyba 
{											// chwilowo jest metoda z postaci xD
	if (collison_dir == CollisionDir::COLLISION_LEFT || collison_dir == CollisionDir::COLLISION_RIGHT)
		velocity.x = 0;
	if (collison_dir == CollisionDir::COLLISION_DOWN)
		velocity.y = 0;
	else if (collison_dir == CollisionDir::COLLISION_UP && velocity.y < 0.0f)
		velocity.y = 0;
}

sf::Vector2f Snowball::get_center_position () const				// w sumie nie wiem po co to przerzucilem tez tu 
{																// usune jak bd dzialac juz all dobrze
	return sprite.getPosition ();
}

void Snowball::set_velocity (sf::Vector2f& dir, const float gravity, const float delta_time)
{
	velocity.y += gravity * delta_time;
}

void Snowball::draw (sf::RenderTarget& target) const
{
	target.draw (sprite);
}