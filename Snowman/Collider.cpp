#include "stdafx.h"
#include "Collider.h"


Collider::Collider(sf::RectangleShape& body) : body{body}
{

}


Collider::~Collider()
{
}

void Collider::move(const float dx, const float dy)
{
	body.move(dx, dy);
}

bool Collider::check_collision(Collider& other, CollisionDir& dir, float push)
{
	sf::Vector2f otherPosition = other.get_position();
	sf::Vector2f otherHalfSize = other.get_half_size();
	sf::Vector2f thisPosition = get_position();
	sf::Vector2f thisHalfSize = get_half_size();

	float deltaX = otherPosition.x - thisPosition.x,
		  deltaY = otherPosition.y - thisPosition.y,
		  intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x),
		  intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				move(intersectX * (1.0f - push), 0.0f);
				other.move(-intersectX * push, 0.0f);
				dir = CollisionDir::COLLISION_RIGHT;
			}
			else
			{
				move(-intersectX * (1.0f - push), 0.0f);
				other.move(intersectX * push, 0.0f);
				dir = CollisionDir::COLLISION_LEFT;
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				move(0.0f, intersectY * (1.0f - push));
				other.move(0.0f, -intersectY * push);
				dir = CollisionDir::COLLISION_DOWN;
			}
			else
			{
				move(0.0f, -intersectY * (1.0f - push));
				other.move(0.0f, intersectY * push);
				dir = CollisionDir::COLLISION_UP;
			}
		}
		return true;
	}
	return false;
}

sf::Vector2f Collider::get_position() const
{
	return body.getPosition() + get_half_size();
}

sf::Vector2f Collider::get_half_size() const
{
	return body.getSize() / 2.0f;
}
