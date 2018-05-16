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
	void set_velocity(sf::Vector2f&);
	static const float SPEED;

};