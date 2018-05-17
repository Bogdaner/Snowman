#include "stdafx.h"
#include "Animation.h"

Animation::Animation (int right)
	:time{ 0.0f }, frame{ 0 }
{
	if(right)
		char_textures = load_textures (1, 9);
	else
		char_textures = load_textures (10, 18);

}

void Animation::set_sprite (sf::RectangleShape& sprite, bool is_moving) const
{
	if (is_moving)
		sprite.setTexture (&char_textures[frame]);
	else
		sprite.setTexture (&char_textures[0]);
}

void Animation::update (float t)
{
	time += t;
	while (time >= HOLD_TIME)
	{
		time -= HOLD_TIME;
		if (++frame >= FRAMES_NUMBER)
			frame = 1;
	}
}

std::vector<sf::Texture> Animation::load_textures (int st, int ed)
{
	std::vector<sf::Texture> to_return;
	sf::Texture tmp;
	std::string name;
	int start = st;
	int end = ed;
	for (int i = start; i <= end; i++)
	{
		name = "textures/walk" + std::to_string (i);
		name += ".png";
		tmp.loadFromFile (name);
		to_return.push_back (tmp);
	}
	return to_return;

}

const int Animation::FRAMES_NUMBER = 9;
const float Animation::HOLD_TIME = 0.1f;