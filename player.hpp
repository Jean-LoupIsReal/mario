#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "instance.hpp"
class player : public instance
{
	sf::Vector2i *_speed;
	bool _onFloor;
	bool _onWall;
	int _jumpFrames;
	int _hp;
public:
	player(const sf::Vector2f pos = sf::Vector2f(300, 600), const sf::Vector2f dim = sf::Vector2f(81, 81), std::string img = "");
	~player();
	void init(const sf::Vector2f& pos, const sf::Vector2f& dim);
	int get_hp();
	void set_speedX(const int& x);
	void set_speedY(const int& y);
	bool jump();
	void playerAction();
	void moveSprite();
	void physics(int dir);
	void hitFloor(int emplacementY);
	void hitWall(int emplacementX);
	void hitCeiling(int emplacementY);
	void grow();
	sf::RectangleShape get_sprite();
};


inline player::player(const sf::Vector2f pos, const sf::Vector2f dim, std::string img):instance(pos, dim, img)
{
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

void player::playerAction(){ 
	int directionX = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		_speed->x += (directionX * 2);
		if (_speed->x > 40)
			_speed->x = 40;
		else if (_speed->x < -40)
			_speed->x = -40;
	}
	else
	{
		_speed->x += (directionX * 1);
		if (_speed->x > 20)
			_speed->x = 20;
		else if (_speed->x < -20)
			_speed->x = -20;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		// la touche "flèche gauche" est enfoncée : on bouge le personnage
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
	physics(directionX);
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

