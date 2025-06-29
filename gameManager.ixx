
module;

import FUNCTIONS;
import CONSTANTS;
import stateMachine;
import assetManager;
import inputManager;
import gameData;

import splashStateHeader;

import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;

export module gameManager;

export class Game
{
public:
    Game(unsigned int width, unsigned int height, std::string title)
    {
        FUNCTIONS::debugLog("\n### GAME SESSION START ###");

        _data->window.create(sf::VideoMode({ width, height }), title, sf::Style::Close | sf::Style::Titlebar);
        
        _data->machine.AddState(StateRef(new SplashState(this->_data)));

        sf::View scaledView(sf::FloatRect( { 0,0 },
            { static_cast<float>(DISPLAY_SCREEN_WIDTH), static_cast<float>(DISPLAY_SCREEN_HEIGHT) }));

        float scaleX = _data->window.getSize().x / SCREEN_WIDTH;
        float scaleY = _data->window.getSize().y / SCREEN_HEIGHT;
        float zoomScale = scaleX > scaleY ? scaleY : scaleX;

        scaledView.setViewport(sf::FloatRect({ 0.f,0.f }, { zoomScale, zoomScale}));

        _data->window.setView(scaledView);

        this->Run();
    }

    ~Game()
    {
        FUNCTIONS::debugLog("### GAME SESSION END ###\n");

    }

private:
    sf::Clock _clock;
    GameDataRef _data = std::make_shared<GameData>();

    void Run()
    {
        double newTime, frameTime, interpolation;

        double currentTime = static_cast<double>(this->_clock.getElapsedTime().asSeconds());
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
