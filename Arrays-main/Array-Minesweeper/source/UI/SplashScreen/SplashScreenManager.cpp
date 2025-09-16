#include "../../header/UI/SplashScreen/SplashScreenManager.h"
#include <iostream>

#include "../../../header/GameLoop/GameLoop.h"
#include "../../../header/Time/TimeManager.h"

namespace UI
{
    SplashScreenManager::SplashScreenManager(sf::RenderWindow* window)
    {
        game_window = window;
        initialize();
    }

    SplashScreenManager::~SplashScreenManager() {}

    void SplashScreenManager::initialize()
    {
        if (!logo_texture.loadFromFile(logo_texture_path))
            std::cerr << "Failed to load logo texture" << std::endl;

        logo_sprite.setTexture(logo_texture);
        logo_sprite.setPosition(getLogoPosition());
    }

    void SplashScreenManager::update() {}

    void SplashScreenManager::render() { drawLogo(); }

    sf::Vector2f SplashScreenManager::getLogoPosition()
    {
        float x_position = (game_window->getSize().x - logo_width) / 2.0f;
        float y_position = (game_window->getSize().y - logo_height) / 2.0f;
        return { x_position, y_position };
    }

    void SplashScreenManager::drawLogo()
    {
        elapsed_time = elapsed_time + Time::TimeManager::getDeltaTime();

        if (elapsed_time < logo_animation_duration)
            game_window->draw(logo_sprite);
        else
        {
            elapsed_time = 0.0f;
            /*GameLoop::setGameState(GameState::GAMEPLAY);*/
        }
    }
}