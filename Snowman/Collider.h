#pragma once
#include <SFML/Graphics.hpp>

enum CollisionDir
{
	COLLISION_LEFT,
	COLLISION_RIGHT,
	COLLISION_UP,
	COLLISION_DOWN,
};

class Collider
{
public:
	Collider();
	~Collider();
	void move(float dx, float dy);
	bool check_collision(Collider& other, CollisionDir& dir,float push);
	sf::Vector2f get_position() const;
	sf::Vector2f get_half_size();
private:
	sf::RectangleShape& body;
};

