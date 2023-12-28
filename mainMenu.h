/********************************************************************************************
* Auteur	: Audy Altis																	*
* Nom		: mainMenu.h																	*
* Date		: 06 décembre 2023																*
* Description : La classe MainMenu permet d'initialiser le menu principal du jeu Mario 		*
*********************************************************************************************/

#pragma once
#include "menu.h"

class mainMenu: public menu{
	public:

		mainMenu();
		~mainMenu();

		void draw(sf::RenderWindow& window);	//Dessiner les options du menu
		void selection(sf::RenderWindow& window);
};
