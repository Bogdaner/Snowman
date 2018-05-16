#pragma once
#include "Object.h"
#include "Collider.h"

class Platform :
	public Object
{
public:
	Platform(const sf::Vector2f& position, const sf::Vector2f& size, sf::Vertex *tile);
	~Platform();
	void update(const float gravity, const float delta_time) override;
private:
	sf::Vertex *tile;
};

