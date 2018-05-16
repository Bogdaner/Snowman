#pragma once
#include "SFML\Graphics.hpp"
#include "Platform.h"
#include <string>
#include <vector>
#include <memory>
#include <fstream>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap();
	~TileMap();
	std::vector<Platform> get_platforms();
private:
	std::vector<Platform> platforms;
	void load_from_file(const std::string s);
	void select_texture(sf::Vertex* v, char tex);
	std::vector<char> tiles;  // array of characters that representing tiles
	sf::VertexArray vertices;
	sf::Texture tileset;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	static const int TILE_WIDTH;
	static const int TILE_HEIGHT;
	int width;
	int height;
	static const std::string No_file;
protected:
};

