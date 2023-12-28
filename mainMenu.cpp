/********************************************************************************************
* Auteur	: Audy Altis																	*
* Nom		: mainMenu.cpp																	*
* Date		: 06 décembre 2023																*
* Description : La classe MainMenu permet d'initialiser le menu principal du jeu Mario 		*
*********************************************************************************************/

#include <iostream>

#include "mainMenu.h"*
#include "config.h"
#include "game.hpp"

using namespace sf;

mainMenu::mainMenu(){

	//Commencer la partie
	_menu[0].setFont(_font);
	_menu[0].setFillColor(Color::Red);
	_menu[0].setString("Commencer une partie");
	_menu[0].setCharacterSize(80);
	_menu[0].setPosition(Vector2f(550, 350));

	//Instruction de jeu
	_menu[1].setFont(_font);
	_menu[1].setFillColor(Color::Blue);
	_menu[1].setString("Instruction");
	_menu[1].setCharacterSize(80);
	_menu[1].setPosition(Vector2f(550, 500));

	//Configuration
	_menu[2].setFont(_font);
	_menu[2].setFillColor(Color::Blue);
	_menu[2].setString("Configuration");
	_menu[2].setCharacterSize(80);
	_menu[2].setPosition(Vector2f(550, 650));

	//Quitter la partie
	_menu[3].setFont(_font);
	_menu[3].setFillColor(Color::Blue);
	_menu[3].setString("Quitter");
	_menu[3].setCharacterSize(80);
	_menu[3].setPosition(Vector2f(550, 800));

	_selection = 0;
}

mainMenu::~mainMenu() {
	_selection = 0;
}

void mainMenu::draw(RenderWindow& window) {
	//Image de texture du fond
	if (!_backgroundTexture.loadFromFile("Ressources/sprite/backgroundMenu.png"))
		exit(1);

	_background.setTexture(_backgroundTexture);

	//Position du fond 
	_background.setScale(static_cast<float>(window.getSize().x) / _background.getLocalBounds().width, 
						 static_cast<float>(window.getSize().y) / _background.getLocalBounds().height);
	
	//son du menu principal
	if (!_menuSound.loadFromFile("Ressources/sound/mainMenu.wav"))
		exit(1);
	      
	//Lecture des sons
		_soundMenu.setBuffer(_menuSound);
		_soundMenu.play();
		_soundMenu.setLoop(true);
	
	while (window.isOpen()) {
		
		while (window.pollEvent(_choiceMenu)) {
			if (_choiceMenu.type == Event::Closed)
				window.close();
			else if (_choiceMenu.type == Event::KeyPressed) {
				switch (_choiceMenu.key.code) {

				case Keyboard::Up:
					setUp();
					break;

				case Keyboard::Down:
					setDown();
					break;

				case Keyboard::Enter:
					selection(window);
					break;

				case Keyboard::Escape:
					window.close();
					break;
				}
			}
		}
		window.clear();;
		window.draw(_background);
		for (int i = 0; i < MAX_MAIN_MENU; i++)
			window.draw(_menu[i]);
		window.display();
	}
}

void mainMenu::selection(RenderWindow& window) {
	config config;

	game game;
	
	_pos = _selection + 1;

	switch (_pos) {

	case 1:
		std::cout << "Test Commencer jeu";
		_soundMenu.stop();

		game.play();
		//Clock timerGame;		//Démarre le chrono pour le classement des joeurs 
		break;

	case 2:
		std::cout << "Test information";
		break;

	case 3:
		_soundMenu.stop();
		config.configuration(window);
		break;

	case 4:
		exit(0);
		break;
	}
}

