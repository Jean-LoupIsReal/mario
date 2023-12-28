/********************************************************************************************
* Auteur	: Audy Altis																	*
* Nom		: menu.h																		*
* Date		: 06 d�cembre 2023																*
* Description : La classe menu permet avec les param�tres pour le menu principal et le menu *
*				pause.																		*
*********************************************************************************************/

#pragma once
#define MAX_MAIN_MENU 4

#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>

class menu {
	protected:
		int _selection,											//Entier qui permet de savoir ou on se situe dans le menu
			_pos;												//Pour la position de l'option selectionn�

		//Pour le texte
		sf::Font _font;
		sf::Text _menu[MAX_MAIN_MENU], _configText;

		//Pour l'affichage
		sf::Event _choiceMenu;
		sf::Sprite _background;
		sf::Texture _backgroundTexture;

		//Pour le son du menuPrincipal
		sf::SoundBuffer _menuSound, _selectionSound;
		sf::Sound _soundMenu, _soundSelection;

	public:
		menu();													//Constructeur
		~menu();												//Desctucteur

		void setPositionBackground(sf::Sprite background);			//Pour le fond d'�cran
		void setUp();											//Option pour monter dans le menu
		void setDown();											//Option pour descendre	dans le menu
		void setLeft();											//Option pour aller � gauche
		void setRight();										//Option pour aller � droite
		void setSelection(int& position);						//Option pour selectionner dans le menu
};