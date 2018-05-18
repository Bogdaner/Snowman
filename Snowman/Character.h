#pragma once
#include "Object.h"
#include "Animation.h"
#include "Snowball.h"

class Character :
	public Object
{
public:
	Character(const sf::Vector2f& position, const sf::Vector2f& size);
	void update(const float gravity, const float delta_time) override;
	CollisionDir collison_dir;
	void on_collision();
	sf::Vector2f get_center_position() const;
	void shooting (sf::RenderWindow& window);
	std::vector<std::unique_ptr<Snowball>> snowballs;
private:
	bool can_shoot;
	bool can_jump;
	void set_velocity(sf::Vector2f& dir, const float gravity, const float delta_time);
	enum class AnimationIndex
	{
		WalkingLeft,
		WalkingRight,
		Count
	};
	Animation animations[int (AnimationIndex::Count)];
	AnimationIndex cur_animation;
	static const float STRENGTH;
	static const float JUMP_HEIGHT;
};