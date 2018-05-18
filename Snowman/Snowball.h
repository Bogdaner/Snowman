#pragma once
#include "Object.h"
class Snowball :
	public Object
{
public:
	Snowball (const sf::Vector2f& direction, const sf::Vector2f& position, const sf::Vector2f& size);
	void update (const float gravity, const float delta_time) override;
	CollisionDir collison_dir;
	void on_collision ();
	sf::Vector2f get_center_position () const;
	void draw (sf::RenderTarget& target) const;
private:
	sf::Texture texture;
	void set_velocity (sf::Vector2f& dir, const float gravity, const float delta_time);
};

