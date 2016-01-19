#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>

class DatTileMap : public sf::Drawable, sf::Transformable
{
public:
	DatTileMap(std::string const& tileset, sf::Vector2u sizeFrame, const int* tileConfiguration,
		unsigned int widthInTile, unsigned int heightInTile);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//methodes pour charger un tileMap
	bool loadingTexture(std::string const& tileset);
	void initializationVertexArray(unsigned int widthInTile, unsigned int heightInTile);
	void fillingVertexArray(sf::Vector2u sizeFrame, const int* tileConfiguration,
		unsigned int widthInTile, unsigned int heightInTile);
	void drawingCharacters(sf::Vector2u sizeFrame, std::vector <std::vector <sf::Vector2u> > placement,
		unsigned int widthInTile, unsigned int heightInTile);

private:
	sf::VertexArray m_vertices;
	sf::Texture* m_tileSet;
};