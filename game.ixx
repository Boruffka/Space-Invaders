
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <string>

export module game;

import constants;
import player;
import enemy;
import stateMachine;
import assetManager;
import inputManager;

struct GameData
{
    StateMachine machine;
    sf::RenderWindow window;
    AssetManager assetManager;
    InputManager inputManager;
};

typedef std::shared_ptr<GameData> GameDataRef;

export class Game
{
public:
    Game(int width, int height, std::string title)
    {
        _data->window.create(sf::VideoMode({width, height}), title, sf::Style::Close | sf::Style::Titlebar);



        this->Run();
    }

private:
    sf::Clock _clock;
    GameDataRef _data = std::make_shared<GameData>();

    Player* player;
    std::vector<Enemy*> enemyVector;

    void Run()
    {
        double newTime, frameTime, interpolation;

        double currentTime = this->_clock.getElapsedTime().asSeconds();
        double accumulator = 0.0f;

        while (this->_data->window.isOpen())
        {
            this->_data->machine.ProcessStateChanges();

            newTime = this->_clock.getElapsedTime().asSeconds();

            frameTime = newTime - currentTime;

            if (frameTime > 0.25f)
            {
                frameTime = 0.25f;
            }

            currentTime = newTime;
            accumulator += frameTime;

            while (accumulator >= DELTA_TIME)
            {
                this->_data->machine.GetActiveState()->HandleInput();
                this->_data->machine.GetActiveState()->Update(DELTA_TIME);

                accumulator -= DELTA_TIME;
            }

            interpolation = accumulator / DELTA_TIME;
            this->_data->machine.GetActiveState()->Draw(interpolation);
        }
    }

};
