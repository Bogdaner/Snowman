#pragma once
#include "Object.h"

class Character :
	public Object
{
public:
	Character(const sf::Vector2f& position, const sf::Vector2f& size);
	void update(const float gravity, const float delta_time) override;
	CollisionDir collison_dir;
	void on_collision();
	sf::Vector2f get_center_position() const;

private:
	bool can_jump;
	void set_velocity(sf::Vector2f& dir, const float gravity, const float delta_time);
	static const float SPEED;
	static const float JUMP_HEIGHT;
};