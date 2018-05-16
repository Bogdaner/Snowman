#pragma once
#include "Object.h"

class Character :
	public Object
{
public:
	Character(const sf::Vector2f& position, const sf::Vector2f& size);
	void update(const float gravity, const float delta_time) override;
	CollisionDir collison_dir;
private:
	std::vector<sf::Texture> CHAR_TEXTURES;
	std::vector<sf::Texture> load_textures ();
	void set_velocity(sf::Vector2f& vel);
	static const float SPEED;
};