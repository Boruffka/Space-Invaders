
module;

import <SFML/Graphics.hpp>;

export module inputManager;

export class InputManager
{
public:
	InputManager() {};
	~InputManager() {};

	bool IsButtonPressed(sf::Keyboard::Scancode key)
	{
		if (sf::Keyboard::isKeyPressed(key))
		{
			return true;
		}
		return false;
	}

	bool IsSpriteClicked(sf::RectangleShape object, sf::Mouse::Button button, sf::RenderWindow& window)
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			sf::IntRect tempRect({(int)object.getPosition().x, (int)object.getPosition().y },
				{ (int)object.getGlobalBounds().size.x, (int)object.getGlobalBounds().size.y });
			
			if (tempRect.contains(sf::Mouse::getPosition(window)))
			{
				return true;
			}
		}
		return false;
	}

	sf::Vector2i GetMousePosition(sf::RenderWindow& window)
	{
		return sf::Mouse::getPosition(window);
	}
};