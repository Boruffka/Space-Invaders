
module;

import CONSTANTS;
import state;
import gameData;
import mainMenuStateHeader;
import gameStateHeader;
import <iostream>;
import <sstream>;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;

export module pauseStateHeader;

export class PauseState : public State
{
public:
	PauseState(GameDataRef data);

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

	sf::RectangleShape _pauseIcon;

	//sf::Text _gameTitle(PIXEL_FONT);
	//Text(const Font& font, String string = "", unsigned int characterSize = 30);
};