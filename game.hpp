#pragma once
#include <SFML/Graphics.hpp>
//#include <iostream>
#include "player.hpp"
#include "map.hpp"
#include "block.hpp"
class game
{
private:
	player* mario;
	sf::RenderWindow window;
	sf::RectangleShape plateform;
	sf::Text _fps;
	sf::Font font;
	map<block> map;

public:
	game();
	void createTestMap();
	~game();
	void draw();
	void drawMap();
	void play();
	void gestColl();

	sf::RectangleShape get_sprite();
};

game::game()
{
	window.create(sf::VideoMode(1900, 1000), "Titre de la fenêtre");
	mario = new player(sf::Vector2f(650, 350), sf::Vector2f(81, 81), "mario-classique.png");
	if (!font.loadFromFile("arial.ttf"))
		std::cout << "erreur";
	_fps.setFont(font);
	_fps.setCharacterSize(24);
	_fps.setString("wait");
	createTestMap();
}

void game::createTestMap() {
	sf::RectangleShape brick;
	sf::RectangleShape coin;

	std::string l[14];
	l[0] =  { "................................................................................................................." };
	l[1] =  { "................................................................................................................." };
	l[2] =  { "...xx............................................................................................................" };
	l[3] =  { "................................................................................................................." };
	l[4] =  { ".................................................................................................................." };
	l[5] =  { "................................................................................................................." };
	l[6] =  { "................................................................................................................." };
	l[7] =  { "................................................................................................................." };
	l[8] =  { "...xx.........xxx................................................................................................" };
	l[9] =  { "...............x................................................................................................." };
	l[10] = { "...............x................................................................................................." };
	l[11] = { "...............x................................................................................................." };
	l[12] = { "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" };
	map.resize(13, l[0].length());
	for (int ligne = 0; ligne < map.nbLine(); ligne++) {
		for (int col = 0; col < map.nbCol(); col++)
		{
			if (l[ligne][col] == 'x')
				map[ligne][col].set_sprite(sf::Vector2f(col * 80,ligne * 80), brick);
		}
	}
}

game::~game()
{
	
}

void game::draw(){
	//imprime les 
	window.clear();
	this->drawMap();
	window.draw(mario->get_sprite());
	window.draw(_fps);
}

inline void game::drawMap()
{
	for (int ligne = 0; ligne < map.nbLine(); ligne++) {
		for (int col = 0; col < map.nbCol(); col++)
		{
			if (map[ligne][col]._isBlock)
				window.draw(map[ligne][col].get_block());
		}
	}
}

inline sf::RectangleShape game::get_sprite()
{
	return mario->get_sprite();
}

void game::play()
{
	int fps = 0;
	sf::Clock clock;
	sf::Clock fpsClock;
	fpsClock.restart();
	sf::Time t1 = sf::milliseconds(30);
	sf::Time tsleep = sf::milliseconds(5);
	sf::Time fpsT = sf::seconds(1);
	sf::Event event;
	while (window.isOpen()){
		
		fps++;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//regarde les input de l'utilisateur
		mario->playerAction();
		gestColl();
		mario->gestSprite();
		mario->moveSprite();
		//Imprime les assets a l'écran
		draw();
		//
		window.display();

		while (clock.getElapsedTime() < t1)
		{
			sleep(tsleep);
		}
		if (fpsClock.getElapsedTime() > fpsT)
		{
			_fps.setString("fps : " + std::to_string(fps));
			fps = 0;
			fpsClock.restart();
		}
		clock.restart();
		
	}

}

inline void game::gestColl()
{

	// Gestion collision de mario
	int posMapX = static_cast<int>(mario->get_pos()->x)/80,
		posMapY = static_cast<int>(mario->get_pos()->y)/80,
		xInBlock = 0,
		yInBlock = 0, 
		xInBlocks = 0,
		yInBlocks = 0,
		x = 0,
		y = 0,
		coinsBlock = 0;	//gère exception ou il y aurait 3 block en meme temps
	if (mario->get_pos()->x < 0)
	{
		mario->hitWall(0);
	}
	else if (mario->get_pos()->y < 0) {
		//il n'y a pas de collision si tu depasse la map
		return;
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			// Comme mario a toujours 1 pixel de plus qu'un block il aura toujours 4 cases à vérifier
			// Si la position de la map est un block
			if (map[posMapY + i][posMapX + j]._isBlock)
			{
				xInBlock = abs(mario->get_pos()->x + j * 81 - (posMapX + 1) * 80);
				yInBlock = abs(mario->get_pos()->y + i * 81 - (posMapY + 1) * 80);
				//s'assure que les 
				if (yInBlocks != yInBlock)
					yInBlocks += yInBlock;
				if (xInBlocks != xInBlock)
					xInBlocks += xInBlock;
				y = i;
				x = j;
				//gère exception ou il y aurait 3 block
				coinsBlock++;
			}
		}
	}
	// Gère exception ou il y aurait 3 block
	if (coinsBlock == 3)
	{
		// Trouve la position non occupé
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
			{
				// Comme mario a toujours 1 pixel de plus qu'un block il aura toujours 4 cases à vérifier
				if (!(map[posMapY + i][posMapX + j]._isBlock))
				{
					// Prends la position non occupé
					mario->hitWall((posMapX + j) * 80);
					if (i == 0)
						mario->hitFloor((posMapY) * 80);
					else
						mario->hitCeiling((posMapY + 1) * 80);
				}
			}
		}
		return;
	}
		 
	//
	if (xInBlocks == 0 || yInBlocks == 0)
		return;

	else if (xInBlocks < yInBlocks)
	{
		if(x == 0)
			mario->hitWall((posMapX + 1) * 80);
		else
			mario->hitWall(posMapX * 80);
	}

	else {
		if (y == 0)
			mario->hitCeiling((posMapY + 1) * 80);
		else
			mario->hitFloor(posMapY * 80);
	}
}