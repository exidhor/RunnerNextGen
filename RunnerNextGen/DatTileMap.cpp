#include "DatTileMap.hpp"

DatTileMap::DatTileMap(std::string const& tileset, sf::Vector2u sizeFrame,
	const int* tileConfiguration, unsigned int widthInTile, unsigned int heightInTile)
{
	loadingTexture(tileset);
	initializationVertexArray(widthInTile, heightInTile);
	fillingVertexArray(sizeFrame, tileConfiguration, widthInTile, heightInTile);

}

//chargement de la texture
bool DatTileMap::loadingTexture(std::string const& tileset)
{
	m_tileSet = new sf::Texture();
	return m_tileSet->loadFromFile(tileset);
}

// initialisation du tableau
void DatTileMap::initializationVertexArray(unsigned int widthInTile, unsigned int heightInTile)
{
	m_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
	m_vertices.resize(widthInTile * heightInTile * 4);
}

void DatTileMap::fillingVertexArray(sf::Vector2u sizeFrame, const int* tileConfiguration, unsigned int widthInTile, unsigned int heightInTile)
{
	// on remplit le tableau de vertex, avec un quad par tuile
	for (unsigned int i = 0; i < widthInTile; ++i) // i en abs
	{
		for (unsigned int j = 0; j < heightInTile; ++j) // j en ord
		{
			// on récupère le numéro de tuile courant
			int tileNumber = tileConfiguration[i + j * widthInTile];

			// on en déduit sa position dans la texture du tileset
			int tu = tileNumber % (m_tileSet->getSize().x / sizeFrame.x); // position en x dans la texture
			int tv = tileNumber / (m_tileSet->getSize().x / sizeFrame.x); // position en y dans la texture

			// on récupère un pointeur vers le quad à définir dans le tableau de vertex
			sf::Vertex* quad = &m_vertices[(i + j * widthInTile) * 4];

			// on définit ses quatre coins dans le rectangle affichage
			quad[0].position = sf::Vector2f(i * sizeFrame.x, j * sizeFrame.y);
			quad[1].position = sf::Vector2f((i + 1) * sizeFrame.x, j * sizeFrame.y);
			quad[2].position = sf::Vector2f((i + 1) * sizeFrame.x, (j + 1) * sizeFrame.y);
			quad[3].position = sf::Vector2f(i * sizeFrame.x, (j + 1) * sizeFrame.y);

			// on définit ses quatre coordonnées de texture
			quad[0].texCoords = sf::Vector2f(tu * sizeFrame.x, tv * sizeFrame.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * sizeFrame.x, tv * sizeFrame.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * sizeFrame.x, (tv + 1) * sizeFrame.y);
			quad[3].texCoords = sf::Vector2f(tu * sizeFrame.x, (tv + 1) * sizeFrame.y);
		}
	}
}

void DatTileMap::drawingCharacters(sf::Vector2u sizeFrame, std::vector <std::vector <sf::Vector2u> > placement,
	unsigned int widthInTile, unsigned int heightInTile)
{
	for (unsigned int i = 0; i < placement.size(); ++i)
	{
		for (unsigned int j = 0; j < placement[i].size(); ++j)
		{
			// on récupère le numéro de tuile courant
			int tileNumber = tileConfiguration[i + j * widthInTile];

			// on en déduit sa position dans la texture du tileset
			int tu = tileNumber % (m_tileSet->getSize().x / sizeFrame.x); // position en x dans la texture
			int tv = tileNumber / (m_tileSet->getSize().x / sizeFrame.x); // position en y dans la texture

			// on récupère un pointeur vers le quad à définir dans le tableau de vertex
			sf::Vertex* quad = &m_vertices[(i + j * widthInTile) * 4];

			// on définit ses quatre coins dans le rectangle affichage
			quad[0].position = sf::Vector2f(i * sizeFrame.x, j * sizeFrame.y);
			quad[1].position = sf::Vector2f((i + 1) * sizeFrame.x, j * sizeFrame.y);
			quad[2].position = sf::Vector2f((i + 1) * sizeFrame.x, (j + 1) * sizeFrame.y);
			quad[3].position = sf::Vector2f(i * sizeFrame.x, (j + 1) * sizeFrame.y);

			// on définit ses quatre coordonnées de texture
			quad[0].texCoords = sf::Vector2f(tu * sizeFrame.x, tv * sizeFrame.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * sizeFrame.x, tv * sizeFrame.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * sizeFrame.x, (tv + 1) * sizeFrame.y);
			quad[3].texCoords = sf::Vector2f(tu * sizeFrame.x, (tv + 1) * sizeFrame.y);
		}
	}
}

void DatTileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// on applique la transformation
	states.transform *= getTransform();

	// on applique la texture du tileset
	states.texture = m_tileSet;

	// et on dessine enfin le tableau de vertex
	target.draw(m_vertices, states);
}

