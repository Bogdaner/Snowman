#pragma once
#include "Object.h"
#include "Animation.h"
#include "Snowball.h"

class Character :
	public Object
{
public:
	Character() = default;
	Character(const sf::Vector2f& position, const sf::Vector2f& size);
	void update(const float gravity, const float delta_time) override;
	CollisionDir collison_dir;
	void on_collision();
	sf::Vector2f get_center_position() const;
	void shooting (sf::RenderWindow& window);
	std::vector<std::shared_ptr<Snowball>> snowballs;
	enum class AnimationIndex
	{
		WalkingLeft,
		WalkingRight,
		Count
	};
	int last_deleted_snowball;     // fuck this shit, I wanna sleep. Temporary! or maybe not 
	AnimationIndex cur_animation;
	int snowballs_count;
private:
	bool can_shoot;
	bool can_jump;
	void set_velocity(sf::Vector2f& dir, const float gravity, const float delta_time);
	Animation animations[int (AnimationIndex::Count)];
	static const float STRENGTH;
	static const float JUMP_HEIGHT;
};