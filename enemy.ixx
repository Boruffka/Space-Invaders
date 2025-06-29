
module;

import CONSTANTS;
import FUNCTIONS;
import state;
import gameData;
import <sstream>;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;

export module enemy;

export class Enemy
{
public:
	Enemy(sf::RectangleShape sprite, float reloadTimer)
	{
		_sprite = sprite;
		_reloadTimer = reloadTimer;
	}

	sf::RectangleShape& getSprite()
	{
		return _sprite;
	}

	float getReloadTimer()
	{
		return _reloadTimer;
	}

	void setReloadTimer(float reloadTimer)
	{
		_reloadTimer = reloadTimer;
	}

	void reduceReloadTimer(float reduction)
	{
		_reloadTimer -= reduction;
	}

private:
	float _reloadTimer;

	sf::RectangleShape _sprite;
};

