
module;

import splashStateHeader;
import FUNCTIONS;
import CONSTANTS;
import state;
import gameData;
import mainMenuStateHeader;
import <iostream>;
import <sstream>;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;

export module splashState;

SplashState::SplashState(GameDataRef data)
	:_data(data)
{

}

void SplashState::Init()
{
	FUNCTIONS::debugLog("[splashState.ixx] Loaded splash");

	this->_data->assetManager.LoadTexture("Splash State Background", SPLASH_STATE_BACKGROUND_PATH);

	const sf::Texture& texture = this->_data->assetManager.GetTexture("Splash State Background");

	_background.setTexture(&texture);
	_background.setSize(sf::Vector2f(
		static_cast<float>(texture.getSize().x),
		static_cast<float>(texture.getSize().y)
	));
}

void SplashState::HandleInput()
{
		while (const std::optional event = this->_data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				FUNCTIONS::debugLog("[splashState.ixx] Window closed");
				this->_data->window.close();
			}
		}
}

void SplashState::Update(double dt)
{
	if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
	{
		FUNCTIONS::debugLog("[splashState.ixx] Entering main menu");
		this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
	}
}

void SplashState::Draw(double dt)
{
	this->_data->window.clear(sf::Color::Black);

	this->_data->window.draw(this->_background);

	this->_data->window.display();
}

void SplashState::Pause()
{

}
	
void SplashState::Resume()
{
	
}