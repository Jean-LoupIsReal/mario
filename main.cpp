/********************************************************************************************
* Auteur	: Audy Altis, Jean-Loup Dandurand-Pominville et Simon Roy						*
* Nom		: main.cpp																		*
* Date		: 06 décembre 2023																*
* Description :																				*
*********************************************************************************************/

#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include <iostream>

#include"list.hpp"
#include"map.hpp"
#include"vecteur.hpp"
#include"mainMenu.h"

using namespace sf;

int main() {
	//jouer jeu
	sf::Texture texture;
	if (!texture.loadFromFile("mario_classique.png"))
	{
		exit(1);
	}
	RenderWindow window(VideoMode::getDesktopMode(), "Mario Paper Kustom");
	Event event;

	mainMenu mainMenu;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();
		mainMenu.draw(window);
		window.display();
	}

	return 0;
}
