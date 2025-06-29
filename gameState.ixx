
import gameStateHeader;
import CONSTANTS;
import FUNCTIONS;
import state;
import gameData;
import pauseStateHeader;
import mainMenuStateHeader;
import <iostream>;
import <sstream>;
import <random>;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;

export module gameState;

GameState::GameState(GameDataRef data)
	:_data(data)
{

}

void GameState::Init()
{
	FUNCTIONS::debugLog("[gameState.ixx] Loaded game");

	_gameOver = false;
	_gameOverDelay = TINY_DELAY;
	
	this->_data->assetManager.LoadTexture("Game State Background", GAME_STATE_BACKGROUND_PATH);
	this->_data->assetManager.LoadTexture("Player Sprite", PLAYER_SPRITE_PATH);
	this->_data->assetManager.LoadTexture("Enemy", ENEMY_SPRITE_PATH);
	this->_data->assetManager.LoadTexture("Bullet", BULLET_SPRITE_PATH);
	this->_data->assetManager.LoadTexture("Heart", HEART_SPRITE_PATH);

	const sf::Texture& texture = this->_data->assetManager.GetTexture("Game State Background");
	const sf::Texture& texture2 = this->_data->assetManager.GetTexture("Player Sprite");
	const sf::Texture& texture3 = this->_data->assetManager.GetTexture("Enemy");
	const sf::Texture& texture7 = this->_data->assetManager.GetTexture("Heart");
	FUNCTIONS::loadTexture(_background, texture);
	
	sf::RectangleShape playerSprite(sf::Vector2f({ BASE_SIZE, BASE_SIZE }));
	playerSprite.setPosition(sf::Vector2f({ (SCREEN_WIDTH - BASE_SIZE) / 2,
		SCREEN_HEIGHT - (BASE_SIZE * 1.5f) }));
	playerSprite.setTexture(&texture2);
	_player = new Player(playerSprite, PLAYER_RELOAD_SPEED);

	_playerAlive = true;
	_playerHealth = 3;

	// ENEMY LAYOUT
	const int rows = 5;
	const int columns = 10;
	const int padding = BASE_SIZE/8;
	const float gridWidth = columns * BASE_SIZE + (columns-1)*padding;
	const float gridHeight = rows * BASE_SIZE + (rows-1)*padding;
	
	float startX = (SCREEN_WIDTH - gridWidth) / 2.f;
	float startY = (SCREEN_HEIGHT - gridHeight) / 2.f;

	_score = 0;
	_stepRightReady = false;
	_enemiesMovingRight = 1;
	_enemiesStepTimer = ENEMY_STEP_TIMER;
	_enemiesStepCounter = ENEMY_STEP_COUNTER/2;
	_totalEnemiesStepCounter = 0;

	// RANDOM
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<> distr(0, ENEMY_RELOAD_SPEED);

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			int evenOffset = row % 2 == 0 ? 1 : 0;
			sf::RectangleShape enemy(sf::Vector2f({BASE_SIZE, BASE_SIZE}));
			enemy.setPosition({ static_cast<float>((startX + col * (BASE_SIZE + padding) + (BASE_SIZE/2)*evenOffset)),
				static_cast<float>((startY + row * (BASE_SIZE + padding)))-BASE_SIZE*2});
			enemy.setTexture(&texture3);
			float randomReload = distr(gen);
			this->_enemies.push_back(Enemy(enemy, randomReload));
		}
	}

	for (int col = 0; col < 3; ++col) {
			sf::RectangleShape heart(sf::Vector2f({ BASE_SIZE, BASE_SIZE }));
			heart.setPosition({ static_cast<float>(col * BASE_SIZE * 1.5f) + BASE_SIZE/2,
				static_cast<float>(BASE_SIZE / 2)});
			heart.setTexture(&texture7);
			this->_playerHearts.push_back(heart);
	}

}

void GameState::HandleInput()
{
	while (const std::optional event = this->_data->window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			FUNCTIONS::debugLog("[gameState.ixx] Window closed");
			this->_data->window.close();
		}

		if (this->_data->inputManager.IsButtonPressed(sf::Keyboard::Scancode::Escape) && _playerAlive)
		{
			FUNCTIONS::debugLog("[gameState.ixx] Game paused");
			this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
		}

		_playerVelocity = 0;
		if (this->_data->inputManager.IsButtonPressed(sf::Keyboard::Scancode::Left))
		{
			this->_playerVelocity = -1;
		}
		if (this->_data->inputManager.IsButtonPressed(sf::Keyboard::Scancode::Right))
		{
			this->_playerVelocity = 1;
		}
		if (this->_data->inputManager.IsButtonPressed(sf::Keyboard::Scancode::Right) &&
			this->_data->inputManager.IsButtonPressed(sf::Keyboard::Scancode::Left))
		{
			_playerVelocity = 0;
		}

		if (this->_data->inputManager.IsButtonPressed(sf::Keyboard::Scancode::Space) && _playerAlive)
		{
			if (_player->getReloadTimer() < 0)
			{
				const sf::Texture& texture4 = this->_data->assetManager.GetTexture("Bullet");
				sf::RectangleShape bullet(sf::Vector2f({ static_cast<float>(texture4.getSize().x), static_cast<float>(texture4.getSize().y) }));
				bullet.setPosition({ static_cast<float>(_player->getSprite().getPosition().x + _player->getSprite().getGlobalBounds().size.x / 2) - bullet.getGlobalBounds().size.x / 2,
					static_cast<float>(_player->getSprite().getPosition().y + _player->getSprite().getGlobalBounds().size.y / 2 - bullet.getGlobalBounds().size.y / 2) });
				bullet.setTexture(&texture4);
				this->_playerBullets.push_back(bullet);

				_player->setReloadTimer(PLAYER_RELOAD_SPEED);
			}
		}
	}
}

void GameState::Update(double dt)
{
	_player->getSprite().move({ static_cast<float>(_playerVelocity * PLAYER_SPEED * dt),0 });
	float currentPos = _player->getSprite().getPosition().x;
	FUNCTIONS::clamp(currentPos, _player->getSprite().getGlobalBounds().size.x * .1f, SCREEN_WIDTH - _player->getSprite().getGlobalBounds().size.x * 1.1f);
	_player->getSprite().setPosition({ currentPos,_player->getSprite().getPosition().y });

	_player->reduceReloadTimer(dt);

	_stepRightReady = false;
	_stepDownReady = false;
	_enemiesStepTimer -= dt;
	if (_enemiesStepTimer < 0)
	{
		_stepRightReady = true;
		_enemiesStepTimer = ENEMY_STEP_TIMER;
		_enemiesStepCounter--;

		if (_enemiesStepCounter < 0)
		{
			_stepDownReady = true;
			_stepRightReady = false;
			_enemiesStepCounter = ENEMY_STEP_COUNTER;
			_totalEnemiesStepCounter++;
			_enemiesMovingRight *= -1;
		}
	}
	
	for (auto& enemy : _enemies)
	{
		if (_stepRightReady)
		{
			enemy.getSprite().move({ static_cast<float>(BASE_SIZE / 2 * _enemiesMovingRight), 0});
		}
		if (_stepDownReady)
		{
			enemy.getSprite().move({ 0, static_cast<float>(BASE_SIZE) });
		}

		enemy.reduceReloadTimer(dt);
		if (enemy.getReloadTimer() < 0)
		{
			const sf::Texture& texture4 = this->_data->assetManager.GetTexture("Bullet");
			sf::RectangleShape bullet(sf::Vector2f({ static_cast<float>(texture4.getSize().x), static_cast<float>(texture4.getSize().y) }));
			bullet.setPosition({ static_cast<float>(enemy.getSprite().getPosition().x + enemy.getSprite().getGlobalBounds().size.x / 2) - bullet.getGlobalBounds().size.x / 2,
				static_cast<float>(enemy.getSprite().getPosition().y + enemy.getSprite().getGlobalBounds().size.y / 2 - bullet.getGlobalBounds().size.y / 2) });
			bullet.setTexture(&texture4); 
			this->_enemyBullets.push_back(bullet);

			enemy.setReloadTimer(ENEMY_RELOAD_SPEED);
		}
	}
	if (_stepRightReady)
	{
		_stepRightReady = false;
	}
	if (_stepDownReady)
	{
		_stepDownReady = false;
	}

	for (auto bulletIt = _playerBullets.begin(); bulletIt != _playerBullets.end(); )
	{
		bool bulletHit = false;
		bulletIt->move({ 0.f, static_cast<float>(-PLAYER_BULLET_SPEED * dt) });

		for (auto enemyIt = _enemies.begin(); enemyIt != _enemies.end(); )
		{
			if (bulletIt->getGlobalBounds().findIntersection(enemyIt->getSprite().getGlobalBounds()).has_value())
			{
				enemyIt = _enemies.erase(enemyIt);
				bulletIt = _playerBullets.erase(bulletIt);
				bulletHit = true;
				_score += 10;
				break;
			}
			else
			{
				++enemyIt;
			}
		}

		if (!bulletHit)
		{
			++bulletIt;
		}
	}
	bool gotHurt = false;
	for (auto it = _enemyBullets.begin(); it != _enemyBullets.end(); )
	{
		it->move({ 0.f, static_cast<float>(ENEMY_BULLET_SPEED * dt) });
		if (it->getPosition().y > SCREEN_HEIGHT * 2)
		{
			it = _enemyBullets.erase(it);
		}

		if (it->getGlobalBounds().findIntersection(_player->getSprite().getGlobalBounds()).has_value())
		{
			it = _enemyBullets.erase(it);
			gotHurt = true;
		}
		else
		{
			++it;
		}
	}
	if (gotHurt)
	{
		_playerHealth--;

		if (!_playerHearts.empty())
		{
			_playerHearts.pop_back();
		}

		if (_playerHealth == 0)
		{
			_playerAlive = false;
		}
	}

	if (!_gameOver)
	{
		if (_enemies.empty() || _totalEnemiesStepCounter > 3 || _playerAlive == false)
		{
			FUNCTIONS::debugLog("[gameState.ixx] Game over with a score of " + std::to_string(_score));
			_gameOver = true;
		}
	}
	if (_gameOver)
	{
		_gameOverDelay -= dt;
		if (_gameOverDelay < 0)
		{
			FUNCTIONS::debugLog("[gameState.ixx] Returning to main menu");
			this->_data->machine.AddState(StateRef(new MainMenuState(_data)));
		}
	}
}

void GameState::Draw(double dt)
{
	this->_data->window.clear(sf::Color::Black);

	this->_data->window.draw(this->_background);

	for (auto enemy : _enemies) 
	{
		this->_data->window.draw(enemy.getSprite());
	}

	for (auto bullet : _playerBullets)
	{
		this->_data->window.draw(bullet);
	}

	for (auto bullet : _enemyBullets)
	{
		this->_data->window.draw(bullet);
	}

	for (auto heart : _playerHearts)
	{
		this->_data->window.draw(heart);
	}

	if (_playerAlive)
	{
		this->_data->window.draw(this->_player->getSprite());
	}

	this->_data->window.display();
}

void GameState::Pause() 
{
	
}

void GameState::Resume() 
{
	
}