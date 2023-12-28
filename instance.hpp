#pragma once
#include <SFML/Graphics.hpp>
class instance {
protected:
	sf::Vector2f* _pos;
	sf::Vector2f* _dim;
	std::string _img;
	sf::RectangleShape _sprite;

public:
	instance(const sf::Vector2f pos = sf::Vector2f(350, 650), const sf::Vector2f dim = sf::Vector2f(80, 80), std::string img = "");
	~instance();
	bool collision(instance s) const;
	sf::Vector2f* get_pos();
	void set_sprite_pos(const sf::Vector2f& pos);
	void set_pos();
	void set_sprite(sf::RectangleShape sprite);
};

instance::instance(const sf::Vector2f pos, const sf::Vector2f dim, std::string img)
{
	_img = img;
	_pos = new sf::Vector2f(pos);
	_dim = new sf::Vector2f(dim);
	_sprite.setPosition(pos);
	_sprite.setSize(dim);
	//img au moment donné
	_sprite.setFillColor(sf::Color(255,0,0));
}

instance::~instance()
{
	delete _pos;
	delete _dim;
}

bool instance::collision(instance s) const
{
	return(_pos->x >= s._pos->x						    //regarde si l'axe des x au point de depart se colisionne
		&& _pos->y >= s._pos->y								//regarde si l'axe des y au point de depart se colisionne
		&& _pos->x + _dim->x >= s._pos->x + s._dim->x		//regarde si l'axe des x au point maximum  se colisionne
		&& _pos->y + _dim->y >= s._pos->y + s._dim->y);		//regarde si l'axe des y au point maximum  se colisionne
}

inline sf::Vector2f* instance::get_pos()
{
	return _pos;
}

inline void instance::set_sprite_pos(const sf::Vector2f& pos)
{
	_sprite.setPosition(pos);
}

inline void instance::set_pos()
{
}

inline void instance::set_sprite(sf::RectangleShape sprite)
{
	_sprite = sprite;
}
