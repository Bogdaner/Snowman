#include "stdafx.h"
#include "Character.h"
#include <iostream>

Character::Character (const sf::Vector2f& position, const sf::Vector2f& size)
	:Object(position, size)
{
	cur_animation = AnimationIndex::WalkingRight;
	animations[int (AnimationIndex::WalkingLeft)] = Animation (int (AnimationIndex::WalkingLeft));
	animations[int (AnimationIndex::WalkingRight)] = Animation (int (AnimationIndex::WalkingRight));
}

void Character::update(const float gravity, const float delta_time)
{
	set_velocity(direction, gravity, delta_time);
	// tu jeszcze bd updateowaæ klatki;
	animations[int (cur_animation)].update (delta_time);
	if (velocity.x == 0)
		animations[int (cur_animation)].set_sprite (sprite, false);
	else
	{
		animations[int (cur_animation)].set_sprite (sprite, true);
	}
	sprite.move(velocity * delta_time);
}

void Character::on_collision()
{
	if (collison_dir == CollisionDir::COLLISION_LEFT || collison_dir == CollisionDir::COLLISION_RIGHT)
		velocity.x = 0;
	if (collison_dir == CollisionDir::COLLISION_DOWN)
	{
		velocity.y = 0;
		can_jump = true;
	}
	else if (collison_dir == CollisionDir::COLLISION_UP && velocity.y < 0.0f)
		velocity.y = 0;
}

sf::Vector2f Character::get_center_position() const
{
	return sprite.getPosition();
}

void Character::set_velocity (sf::Vector2f& dir, const float gravity, const float delta_time)
{
	dir = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir.x = 1.0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir.x = -1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && can_jump)
	{
		velocity.y = -sqrtf(2.0f * gravity * JUMP_HEIGHT);
		can_jump = false;
	}
	if (collison_dir == CollisionDir::NO_COLLISION)
		can_jump = false;

	velocity.y += gravity * delta_time;
	velocity.x = dir.x * SPEED;

	if (direction.x > 0.0f)
		cur_animation = AnimationIndex::WalkingRight;
	else if (direction.x < 0.0f)
		cur_animation = AnimationIndex::WalkingLeft;

}

void Character::shooting(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed (sf::Mouse::Button::Left) && !can_shoot) {
		sf::Vector2f on_window_pos = (sf::Vector2f)window.getSize () / 2.0f;		// postaæ jest zawsze na œrodku 										// wiêc window size / 2 daje gdzie jest postaæ 
		can_shoot = true;															// wzg ekranu 
		sf::Vector2i throw_click;
		throw_click = sf::Mouse::getPosition (window);								
		float relx = throw_click.x - on_window_pos.x;								// proporcje 
		float rely = throw_click.y - on_window_pos.y;
		float relmax = abs (rely) + abs (relx);
		relx = relx / relmax;
		rely = rely / relmax;
		snowballs.push_back (std::unique_ptr<Snowball> (new Snowball ({ relx * STRENGTH, rely * STRENGTH },
			{ sprite.getPosition().x, sprite.getPosition().y}, { 25.0f,25.0f })));
	}
	else if (!sf::Mouse::isButtonPressed (sf::Mouse::Button::Left)) {				// ¿eby jeden klik == jeden strza³ 
		can_shoot = false;
	}
}

const float Character::STRENGTH = 8.5f;												// si³a rzutu -> wiêksza == œnie¿ka leci dalej
const float Character::JUMP_HEIGHT = 250.0f;