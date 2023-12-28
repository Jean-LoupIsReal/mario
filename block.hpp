#pragma once
#include "instance.hpp"
class block
{
private:
	sf::RectangleShape* _block;										// L'affichage du block
	sf::Texture _texture;
public:
	bool _isBlock;													//S'assure que le block est solide
	block(bool b = false);											//
	~block();
	void set_block(bool);
	void set_sprite(sf::Vector2f pos, sf::RectangleShape sprite);
	sf::RectangleShape get_block();

};

block::block(bool b)
{
	_block = nullptr;
	this->_isBlock = b;
}

block::~block()
{
	delete _block;
}

inline void block::set_block(bool b)
{
	this->_isBlock = b;
}

inline void block::set_sprite(sf::Vector2f pos, sf::RectangleShape sprite)
{
	_isBlock = true;
	_block = new sf::RectangleShape();
	_block->setSize(sf::Vector2f(80, 80));
	_block->setFillColor(sf::Color(0, 255, 0));
	_block->setPosition(pos);
}

inline sf::RectangleShape block::get_block()
{
	return *_block;
}
