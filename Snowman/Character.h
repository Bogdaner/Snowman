#pragma once
#include "Object.h"
#include "Collider.h"

class Character :
	public Object
{
public:
	Character(const sf::Vector2f&);
	void draw(sf::RenderTarget&) const override;
	void update(const float gravity, const float delta_time) override;
private:
	void set_velocity(sf::Vector2f&);
	Collider get_collider();
	static const float SPEED;

};