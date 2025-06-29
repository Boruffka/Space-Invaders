
module;

import pauseStateHeader;
import FUNCTIONS;
import CONSTANTS;
import state;
import gameData;
import mainMenuStateHeader;
import gameStateHeader;
import <iostream>;
import <sstream>;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;

export module pauseState;

PauseState::PauseState(GameDataRef data)
	:_data(data)
{

}

void PauseState::Init()
{
	FUNCTIONS::debugLog("[pauseState.ixx] Loaded pause state");

	this->_data->assetManager.LoadTexture("Pause State Background", PAUSE_STATE_BACKGROUND_PATH);
	this->_data->assetManager.LoadTexture("Pause State Icon", PAUSE_STATE_ICON_PATH);

	const sf::Texture& texture = this->_data->assetManager.GetTexture("Pause State Background");
	_background.setTexture(&texture); // Note: setTexture takes a pointer now
	_background.setSize(sf::Vector2f(
		static_cast<float>(texture.getSize().x),
		static_cast<float>(texture.getSize().y)
	));

	const sf::Texture& texture2 = this->_data->assetManager.GetTexture("Pause State Icon");
	_pauseIcon.setTexture(&texture2);
	_pauseIcon.setSize(sf::Vector2f(
		static_cast<float>(texture2.getSize().x),
		static_cast<float>(texture2.getSize().y)
	));

	this->_pauseIcon.setPosition(sf::Vector2f(SCREEN_WIDTH - (this->_pauseIcon.getGlobalBounds().size.x * 1.1),
		this->_pauseIcon.getGlobalBounds().size.y * 0.1));
}

void PauseState::HandleInput()
{
	while (const std::optional event = this->_data->window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			this->_data->window.close();
		}

		if (this->_data->inputManager.IsButtonPressed(sf::Keyboard::Scancode::Space))
		{
			this->_data->machine.RemoveState();
		}

		if (this->_data->inputManager.IsButtonPressed(sf::Keyboard::Scancode::R))
		{
			FUNCTIONS::debugLog("[pauseState.ixx] Returning to game");
			this->_data->machine.RemoveState();

			this->_data->machine.AddState(StateRef(new MainMenuState(_data)),true);
		}
	}
}

void PauseState::Update(double dt)
{

}

void PauseState::Draw(double dt)
{
	this->_data->window.clear(sf::Color::Black);

	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_pauseIcon);

	this->_data->window.display();
}

void PauseState::Pause() 
{
	
}

void PauseState::Resume() 
{
	
}