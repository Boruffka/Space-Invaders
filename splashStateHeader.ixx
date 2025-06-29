
module;

import CONSTANTS;
import state;
import gameData;
import mainMenuState;
import <iostream>;
import <sstream>;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;

export module splashStateHeader;

export class SplashState : public State
{
public:
	SplashState(GameDataRef data);

	void Init();

	void HandleInput();

	void Update(double dt);

	void Draw(double dt);

	void Pause();

	void Resume();

private:
	GameDataRef _data;

	sf::Clock _clock;

	sf::RectangleShape _background;
};