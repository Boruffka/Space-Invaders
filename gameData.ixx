
module;

#include <SFML/Graphics.hpp>
#include <memory>

import CONSTANTS;
import stateMachine;
import assetManager;
import inputManager;

export module gameData;

export struct GameData
{
    StateMachine machine;
    sf::RenderWindow window;
    AssetManager assetManager;
    InputManager inputManager;
};

export typedef std::shared_ptr<GameData> GameDataRef;
