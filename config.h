/********************************************************************************************
* Auteur	: Audy Altis																	*
* Nom		: config.h																		*
* Date		: 12 décembre 2023																*
* Description : classe config qui aura les paramètres pour changer le son, les touche et    *
*				la langue.																	*
*********************************************************************************************/
#pragma once

#include<fstream>
#include "menu.h"

class config: public menu {
	private:
		std::ifstream _configuration;
		std::string _title;
		int _volume;

	public:
		config();
		~config();

		void init(); //Initialise les configuration par défaut du jeu
		void readFile();
		void writeFile();

		void configuration(sf::RenderWindow& window);
		void selectConfig(sf::RenderWindow& window);
};

