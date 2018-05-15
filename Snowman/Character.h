#pragma once
#include "Object.h"

class Character :
	public Object
{
private:
	static constexpr float speed = 100.0f;
public:
	Character (const sf::Vector2f&);
	void draw (sf::RenderTarget&) const;
	void update (const float&, const float&);
	void set_direction (const sf::Vector2f&);
};