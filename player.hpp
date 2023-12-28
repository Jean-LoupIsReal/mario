#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "instance.hpp"
class player : public instance
{
	sf::Vector2i* _speed;
	bool _onFloor;
	bool _onWall;
	int _jumpFrames,
		_hp,
		_directionX,
		_directionSprite,
		*_marioTexture;

public:
	player(const sf::Vector2f pos = sf::Vector2f(300, 600), const sf::Vector2f dim = sf::Vector2f(81, 81), std::string img = "");
	~player();
	void init(const sf::Vector2f& pos, const sf::Vector2f& dim);
	int get_hp();
	void set_speedX(const int& x);
	void set_speedY(const int& y);
	void gestSprite();
	void playerAction();
	void moveSprite();
	void physics(int dir);
	void hitFloor(int emplacementY);
	void hitWall(int emplacementX);
	void hitCeiling(int emplacementY);
	void grow();
	sf::RectangleShape get_sprite();
};


inline player::player(const sf::Vector2f pos, const sf::Vector2f dim, std::string img) :instance(pos, dim, img)
{
	_marioTexture = new int[13];

	// Pointe vers la gauche
	_marioTexture[0] = 30;	//Jump
	_marioTexture[1] = 61; 
	_marioTexture[2] = 90;
	_marioTexture[3] = 113;
	_marioTexture[4] = 146;
	_marioTexture[5] = 181;
	//Pointe vers la droite
	_marioTexture[6] = 208;
	_marioTexture[7] = 239;
	_marioTexture[8] = 271;
	_marioTexture[9] = 299;
	_marioTexture[10] = 327;
	_marioTexture[11] = 360;
	_marioTexture[12] = 405; //mort

	_directionX = 0;
	_directionSprite = 1;
	_hp = 1;
	_jumpFrames = 0;
	_onFloor = false;
	_onWall = false;
	_speed = new sf::Vector2i(0, 0);
	_sprite.setPosition(pos);
	_sprite.setSize(dim);
}

inline player::~player()
{
	delete _speed;
	delete _marioTexture;
}

void player::init(const sf::Vector2f& pos, const sf::Vector2f& dim) {
	*_pos = pos;
	*_dim = dim;
}
inline int player::get_hp()
{
	return _hp;
}

void player::set_speedX(const int& x)
{
	_speed->x = x;
}

void player::set_speedY(const int& y)
{
	_speed->y = y;
}

inline void player::gestSprite()
{
	int numSprite = 0;
	if (_directionSprite == 1) {
		numSprite = 6;
	}
	else
	{
		numSprite = 5;
	}
	if (!_onFloor)
	{
		numSprite += 5 * _directionSprite;
	}
	//si l'utilisateur ne bouge pas
	if(_onFloor && abs(_directionX) == 1)
	{
		_directionSprite = _directionX;
	}
	set_textureRect(sf::IntRect(_marioTexture[numSprite], 0, 16, 16));
}

void player::playerAction() {
	_directionX = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		_speed->x += (_directionX * 2);
		if (_speed->x > 40)
			_speed->x = 40;
		else if (_speed->x < -40)
			_speed->x = -40;
	}
	else
	{
		_speed->x += (_directionX * 1);
		if (_speed->x > 20)
			_speed->x = 20;
		else if (_speed->x < -20)
			_speed->x = -20;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		// la touche "fl�che gauche" est enfonc�e : on bouge le personnage
		if (_jumpFrames < 10)
		{
			set_speedY(-32);
			_jumpFrames++;
		}

	}
	else
	{
		_jumpFrames = 20;
	}
	physics(_directionX);
}

inline void player::moveSprite()
{
	_sprite.setPosition(_pos->x, _pos->y);
}

inline void player::physics(int dir)
{
	if (dir == 0)
	{
		if (_speed->x > 0)
			_speed->x -= 1;
		if (_speed->x < 0)
			_speed->x += 1;
	}
	if (!_onFloor)
	{
		_speed->y += 5;
	}
	_speed->y = std::min(_speed->y, 60);
	_pos->x += _speed->x;
	_pos->y += _speed->y;
	_onFloor = false;
}
inline void player::hitFloor(int emplacementY) {
	_speed->y = 0;
	_pos->y = emplacementY;
	_onFloor = true;
	_jumpFrames = 0;
}
inline void player::hitWall(int emplacementX) {
	_speed->x = 0;
	_pos->x = emplacementX;
}
inline void player::hitCeiling(int emplacementY)
{
	_speed->y = 0;
	_pos->y = emplacementY;
	_jumpFrames = 20;
}
inline void player::grow()
{
	_hp = 2;
}
inline sf::RectangleShape player::get_sprite()
{
	return _sprite;
}

