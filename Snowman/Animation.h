#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation () = default;			// rozwi¹zanie chwilowe z right
	Animation (int right);			// wiec nie spinaj dupy kappa xD
	void set_sprite (sf::RectangleShape& sprite, bool is_moving) const;
	void update (float t);
	int frame;
private:
	std::vector<sf::Texture> char_textures;
	std::vector<sf::Texture> load_textures (int start, int end);
	static const int FRAMES_NUMBER;
	static const float HOLD_TIME;
	float time;
	
protected:

};
