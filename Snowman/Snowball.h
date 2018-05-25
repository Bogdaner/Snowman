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
	void draw (sf::RenderTarget& target) const;
	enum class delete_steps {
		no_collision,
		after_collision,
		to_del
	};
	delete_steps delete_step;
	int id;
private:
	float time_of_death;
	static int count;
	static const float TIME_TO_ERASING;
	sf::Texture texture;
	void set_velocity (sf::Vector2f& dir, const float gravity, const float delta_time);
};

