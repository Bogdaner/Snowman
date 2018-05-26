#pragma once
#include <SFML/Graphics.hpp>

enum CollisionDir
{
	COLLISION_LEFT,
	COLLISION_RIGHT,
	COLLISION_UP,
	COLLISION_DOWN,
	NO_COLLISION,
};

class Collider
{
public:
	Collider() = default;
	Collider(sf::RectangleShape* body);
	~Collider();
	void move(const float dx, const float dy);
	bool check_collision(Collider& other, CollisionDir& dir, float push);
	sf::Vector2f get_position() const;
	sf::Vector2f get_half_size() const;
private:
	sf::RectangleShape* body;
};

