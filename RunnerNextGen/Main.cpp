#include <SFML/Graphics.hpp>
#include "TileMap.hpp"
#include "DatTileMap.hpp"

#define NB_TILE_WIDTH 12
#define NB_TILE_HEIGHT 8
#define TILE_SIZE_X 32
#define TILE_SIZE_Y 48

int main()
{
	// on cr�e la fen�tre
	sf::RenderWindow window(sf::VideoMode(512, 256), "Tilemap");

	// on d�finit le niveau � l'aide de num�ro de tuiles
	const int level[] =
	{
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
	};

	// on cr�e la tilemap avec le niveau pr�c�demment d�fini
	TileMap map;
	if (!map.load("Img/TileMap", sf::Vector2u(32, 32), level, 16, 8))
		/*return -1*/;

	std::string path("Img/TileMap");

	DatTileMap tileMap(path, sf::Vector2u(32, 32), level, 16, 8);

	// on fait tourner la boucle principale
	while (window.isOpen())
	{
		// on g�re les �v�nements
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// on dessine le niveau
		window.clear();
		window.draw(tileMap);
		window.display();
	}

	return 0;
}