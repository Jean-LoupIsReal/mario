#pragma once
#include <SFML/Graphics.hpp>
class instance {
protected:
	sf::Vector2f* _pos;
	sf::Vector2f* _dim;
	sf::Vector2i* _dimTexture;
	std::string _img;
	sf::RectangleShape _sprite;
	sf::Texture _texture;
public:
	instance(const sf::Vector2f pos = sf::Vector2f(0, 0), const sf::Vector2f dim = sf::Vector2f(80, 80), std::string img = "", sf::IntRect textureRect = sf::IntRect(208, 0, 16, 16));
	~instance();
	bool collision(instance s) const;
	sf::Vector2f* get_pos();
	void set_sprite_pos(const sf::Vector2f& pos);
	void set_pos();
	void set_textureRect(sf::IntRect textureRect);
};

instance::instance(const sf::Vector2f pos, const sf::Vector2f dim, std::string img, sf::IntRect textureRect)
{
	_img = img;
	_pos = new sf::Vector2f(pos);
	_dim = new sf::Vector2f(dim);
	_dimTexture = new sf::Vector2i(12, 15);
	_sprite.setPosition(pos);
	_sprite.setSize(dim);
	if (!_texture.loadFromFile("mario_classique.png"))
	{
		std::cout << "erreur load from file ressources/sprite/" << img << " de l'objet instance.hpp";
		exit(1);
	}
	_sprite.setTexture(&_texture);
	_sprite.setTextureRect(textureRect);
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

inline void instance::set_textureRect(sf::IntRect textureRect)
{
	_sprite.setTextureRect(textureRect);
}
