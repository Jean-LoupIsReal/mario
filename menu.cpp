/********************************************************************************************
* Auteur	: Audy Altis																	*
* Nom		: menu.cpp																		*
* Date		: 06 décembre 2023																*
* Description : Les fonction global des menus du jeu										*
*********************************************************************************************/

#include"menu.h"

using namespace sf;

menu::menu() {
	if (!_font.loadFromFile("ressources/font/regular.ttf"))
		exit(1);

	_menu[0] = _configText = Text();
	_choiceMenu = Event();
	_background = Sprite();
	_backgroundTexture = Texture();

	_selection = _pos = 0;
}

menu::~menu() {
	_menu[0] = _configText= Text();
	_choiceMenu = Event();
	_background = Sprite();
	_backgroundTexture = Texture();

	_selection = _pos = 0;
}

void menu::setPositionBackground(Sprite background) {
	_background = background;
}

void menu::setUp() {
	if (_selection - 1 >= -1) {
		_menu[_selection].setFillColor(Color::Blue);
		_selection--;

		if (_selection == -1)
			_selection = 3;
		
		_menu[_selection].setFillColor(Color::Red);
	}
}

void menu::setDown() {
	if (_selection + 1 <= MAX_MAIN_MENU) {
		_menu[_selection].setFillColor(Color::Blue);
		_selection++;

		if (_selection == 4)
			_selection = 0;
	
		_menu[_selection].setFillColor(Color::Red);
	}
}

void menu::setLeft() {

}

void menu::setRight() {

}

void menu::setSelection(int& position) {
	_pos = position;
}