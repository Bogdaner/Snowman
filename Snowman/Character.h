#pragma once
#include "SFML/Main.hpp"
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
	bool is_moving;
	enum AnimationIndex
	{
		WalkingLeft,
		WalkingRight,
		Count
	};
	AnimationIndex cur_animation;
	Animation animations[int (AnimationIndex::Count)];
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	int hp;
	int last_deleted_snowball;     // Temporary! or maybe not... 
private:
	sf::Font font;
	bool can_shoot;
	bool can_jump;
	void set_velocity(sf::Vector2f& dir, const float gravity, const float delta_time);
	static const float STRENGTH;
	static const float JUMP_HEIGHT;
	static const std::string CantLoadFont;
};