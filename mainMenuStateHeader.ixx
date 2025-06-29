
module;

import CONSTANTS;
import <thread>;
import <future>;
import state;
import gameData;
import gameStateHeader;
import <iostream>;
import <sstream>;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;

export module mainMenuStateHeader;

export class MainMenuState : public State
{
public:
	MainMenuState(GameDataRef data);

	void Init();

	void HandleInput();

	void Update(double dt);

	void Draw(double dt);

	void Pause();

	void Resume();

private:
	std::future<void> _assetLoading;
	bool _assetsLoaded = false;

	GameDataRef _data;

	int chosenElement{ 1 };

	sf::Clock _clock;

	sf::RectangleShape _background;

	sf::RectangleShape _playButton;

	sf::RectangleShape _exitButton;

	//Text(const Font& font, String string = "", unsigned int characterSize = 30);
};