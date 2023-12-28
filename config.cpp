#include "config.h"
#include "mainMenu.h"

#include <iostream>

using namespace sf;

config::config() {

	//Volume
	_menu[0].setFont(_font);
	_menu[0].setFillColor(Color::Red);
	_menu[0].setString("Volume");
	_menu[0].setCharacterSize(80);
	_menu[0].setPosition(Vector2f(550, 350));

	//Périphérique
	_menu[1].setFont(_font);
	_menu[1].setFillColor(Color::Blue);
	_menu[1].setString("Clavier");
	_menu[1].setCharacterSize(80);
	_menu[1].setPosition(Vector2f(550, 500));

	//Langue
	_menu[2].setFont(_font);
	_menu[2].setFillColor(Color::Blue);
	_menu[2].setString("Langue");
	_menu[2].setCharacterSize(80);
	_menu[2].setPosition(Vector2f(550, 650));

	//Retour menu Principal
	_menu[3].setFont(_font);
	_menu[3].setFillColor(Color::Blue);
	_menu[3].setString("Retour");
	_menu[3].setCharacterSize(80);
	_menu[3].setPosition(Vector2f(550, 800));

	_selection = 0;
	_volume = 100;
}

config::~config() {
	_volume = _selection = 0;
}

void config::configuration(RenderWindow& window) {
	//Image de texture du fond
	if (!_backgroundTexture.loadFromFile("Ressources/sprite/backgroundOther.png"))
		exit(1);

	_background.setTexture(_backgroundTexture);

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

				case Keyboard::Right:
					setRight();
					break;

				case Keyboard::Left:
					setLeft();
					break;

				case Keyboard::Enter:
					selectConfig(window);
					break;

				case Keyboard::Escape:
					window.close();
					break;
				}
			}

		}
		window.clear();
		window.draw(_background);
		for (int i = 0; i < MAX_MAIN_MENU; i++)
			window.draw(_menu[i]);
		window.display();
	}
}

void config::selectConfig(RenderWindow& window) {
	mainMenu menu;
	float test = _soundMenu.getVolume();
	_pos = _selection + 1;

	switch (_pos) {

	case 1:
		//Changer Volume 
		std::cout << test;
		break;

	case 2:
		//Changer le periphérique
		break;

	case 3:
		//Changer la langue
		break;

	case 4:
		menu.draw(window);
		break;
	}
}