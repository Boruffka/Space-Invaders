
module;

import mainMenuStateHeader;
import CONSTANTS;
import FUNCTIONS;
import state;
import gameData;
import gameStateHeader;
import <iostream>;
import <sstream>;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;

export module mainMenuState;

MainMenuState::MainMenuState(GameDataRef data)
	:_data(data)
{

}

void MainMenuState::Init()
{
	this->_data->assetManager.LoadTexture("Main Menu State Background", MAIN_MENU_STATE_BACKGROUND_PATH);
	this->_data->assetManager.LoadTexture("Main Menu Play Button", MAIN_MENU_PLAY_BUTTON_PATH);
	this->_data->assetManager.LoadTexture("Main Menu Exit Button", MAIN_MENU_EXIT_BUTTON_PATH);

	const sf::Texture& texture = this->_data->assetManager.GetTexture("Main Menu State Background");
	_background.setTexture(&texture); 
	_background.setSize(sf::Vector2f(
		static_cast<float>(texture.getSize().x),
		static_cast<float>(texture.getSize().y)
	));

	const sf::Texture& texture2 = this->_data->assetManager.GetTexture("Main Menu Play Button");
	_playButton.setTexture(&texture2);
	_playButton.setSize(sf::Vector2f(
		static_cast<float>(texture2.getSize().x),
		static_cast<float>(texture2.getSize().y)
	));

	const sf::Texture& texture3 = this->_data->assetManager.GetTexture("Main Menu Exit Button");
	_exitButton.setTexture(&texture3);
	_exitButton.setSize(sf::Vector2f(
		static_cast<float>(texture3.getSize().x),
		static_cast<float>(texture3.getSize().y)
	));

	this->_playButton.setPosition(sf::Vector2f((SCREEN_WIDTH / 2) - (this->_playButton.getGlobalBounds().size.x / 2),
		(SCREEN_HEIGHT / 3) - this->_playButton.getGlobalBounds().size.y / 2));
	this->_exitButton.setPosition(sf::Vector2f((SCREEN_WIDTH / 2) - (this->_exitButton.getGlobalBounds().size.x / 2),
		(SCREEN_HEIGHT / 3 * 2) - this->_exitButton.getGlobalBounds().size.y / 2));
}

void MainMenuState::HandleInput()
{
	while (const std::optional event = this->_data->window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			FUNCTIONS::debugLog("[mainMenuState.ixx] Window closed");
			this->_data->window.close();
		}

		if (this->_data->inputManager.IsButtonPressed(sf::Keyboard::Scancode::Up))
		{
			chosenElement++;
		}
			
		if (this->_data->inputManager.IsButtonPressed(sf::Keyboard::Scancode::Down))
		{
			chosenElement--;
		}

		if (this->_data->inputManager.IsButtonPressed(sf::Keyboard::Scancode::Space))
		{
			if (chosenElement == 1)
			{
				FUNCTIONS::debugLog("[mainMenuState.ixx] Entering game");
				this->_data->machine.AddState(StateRef(new GameState(_data)));
			}
			if (chosenElement == 0)
			{
				FUNCTIONS::debugLog("[mainMenuState.ixx] Closing window");
				this->_data->window.close();
			}
		}
	}
}

void MainMenuState::Update(double dt)
{

}

void MainMenuState::Draw(double dt)
{
	FUNCTIONS::clamp(chosenElement, 0, 1);

	if (chosenElement == 1)
	{
		this->_playButton.setScale({ 1.1f, 1.1f });
		this->_exitButton.setScale({ 1.f, 1.f });
	}
	if (chosenElement == 0)
	{
		this->_playButton.setScale({ 1.f, 1.f });
		this->_exitButton.setScale({ 1.1f, 1.1f });
	}

	this->_data->window.clear(sf::Color::Black);

	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_playButton);
	this->_data->window.draw(this->_exitButton);

	this->_data->window.display();
}

void MainMenuState::Pause() 
{
	
}

void MainMenuState::Resume() 
{
	
}