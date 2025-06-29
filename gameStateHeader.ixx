
module;

import CONSTANTS;
import state;
import gameData;
import enemy;
import player;
import <iostream>;
import <sstream>;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;

export module gameStateHeader;

export class GameState : public State
{
public:
	GameState(GameDataRef data);

	void Init();

	void HandleInput();

	void Update(double dt);

	void Draw(double dt);

	void Pause();

	void Resume();

private:
	GameDataRef _data;

	sf::Clock _clock;

	bool _gameOver;
	float _gameOverDelay;

	sf::RectangleShape _background;

	Player* _player;
	bool _playerAlive;
	int _playerHealth;
	std::list<sf::RectangleShape> _playerHearts;


	int _playerVelocity;

	std::list<Enemy> _enemies;
	

	int _score;

	bool _stepRightReady;
	bool _stepDownReady;
	int _enemiesMovingRight;
	float _enemiesStepTimer;
	float _enemiesStepCounter;
	int _totalEnemiesStepCounter;

	std::list<sf::RectangleShape> _playerBullets;
	std::list<sf::RectangleShape> _enemyBullets;

	//sf::Text _gameTitle(PIXEL_FONT);
	//Text(const Font& font, String string = "", unsigned int characterSize = 30);
};