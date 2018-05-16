#include "stdafx.h"
#include "Character.h"

Character::Character (const sf::Vector2f& position, const sf::Vector2f& size)
	:Object(position, size)
{
	CHAR_TEXTURES = load_textures ();
	sprite.setTexture (&CHAR_TEXTURES[0]);
}

void Character::update(const float gravity, const float delta_time)
{
	set_velocity(direction);
	// tu jeszcze bd updateowaæ klatki;
	sprite.move(velocity * delta_time);
}

void Character::set_velocity (sf::Vector2f& dir)
{
	dir = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir.x = 1.0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir.x = -1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir.y = -1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir.y = 1.0f;
	//{
	//	// jump
	//}
	velocity = dir * SPEED;
	// tu te¿ animacja bd siê zmieniaæ;
}

std::vector<sf::Texture> Character::load_textures ()
{
	std::vector<sf::Texture> to_return;
	sf::Texture tmp;
	std::string name;
	for (int i = 1; i <= 9; i++)
	{
		name = "textures/walk" + std::to_string (i);
		name += ".png";
		tmp.loadFromFile (name);
		to_return.push_back (tmp);
	}
	return to_return;

}

const float Character::SPEED = 100.0f;