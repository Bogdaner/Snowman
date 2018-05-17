#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
{
	tileset.loadFromFile("textures/tiles.png");
	tileset.setSmooth(false);
	load_from_file("level.txt");
	for(int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			//get pointer to the current tile quad
			sf::Vertex *quad = &vertices[(i + j * width) * 4];
			quad[0].position = sf::Vector2f(float(i * TILE_WIDTH) , float(j * TILE_HEIGHT));
			quad[1].position = sf::Vector2f(float((i + 1) * TILE_WIDTH), float(j * TILE_HEIGHT));
			quad[2].position = sf::Vector2f(float((i + 1) * TILE_WIDTH), float((j + 1) * TILE_HEIGHT));
			quad[3].position = sf::Vector2f(float(i * TILE_WIDTH), float((j + 1) * TILE_HEIGHT));

			select_texture(quad, tiles[i + j * width]);
		}
}

TileMap::~TileMap()
{

}

std::vector<Platform> TileMap::get_platforms()
{
	return platforms;
}

void TileMap::load_from_file(const std::string s)
{
	std::unique_ptr<std::fstream> fs{ new std::fstream{s, fs->in} };
	if (!(*fs)) throw No_file;
	*fs >> width >> height;
	vertices.resize(width * height * 4);
	vertices.setPrimitiveType(sf::Quads);

	while (fs->good())
	{
		char tmp;
		*fs >> tmp;
		tiles.push_back(tmp);
	}
}

void TileMap::select_texture(sf::Vertex* v, char tex)
{
	sf::Vector2f tmp;
	bool is_platform = false;
	switch (tex)
	{
	case '.':
		tmp.x = 7, tmp.y = 4;
		break;
	case 'z':
		tmp.x = 8, tmp.y = 12;
		is_platform = true;
		break;
	default:
		tmp.x = 0, tmp.y = 0;
	}

	v[0].texCoords = sf::Vector2f(tmp.x * TILE_WIDTH + 2 * tmp.x, tmp.y * TILE_HEIGHT + 2 * tmp.y);
	v[1].texCoords = sf::Vector2f((tmp.x + 1) * TILE_WIDTH + 2 * tmp.x, tmp.y * TILE_HEIGHT + 2 * tmp.y);
	v[2].texCoords = sf::Vector2f((tmp.x + 1) * TILE_WIDTH + 2 * tmp.x, (tmp.y + 1) * TILE_HEIGHT + 2 * tmp.y);
	v[3].texCoords = sf::Vector2f(tmp.x * TILE_WIDTH + 2 * tmp.x, (tmp.y + 1) * TILE_HEIGHT + 2 * tmp.y);

	if (is_platform == true)
		platforms.push_back(Platform(sf::Vector2f(v[0].position.x + TILE_WIDTH / 2, v[0].position.y + TILE_HEIGHT / 2), sf::Vector2f((float)TILE_WIDTH, (float)TILE_HEIGHT), v));;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &tileset;
	target.draw(vertices, states);
}

const int TileMap::TILE_HEIGHT = 70;

const int TileMap::TILE_WIDTH = 70;

const std::string TileMap::No_file = "No such file!";