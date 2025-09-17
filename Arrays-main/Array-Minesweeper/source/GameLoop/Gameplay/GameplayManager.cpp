#include "../../header/GameLoop/Gameplay/GameplayManager.h"

namespace Gameplay
{
    GameplayManager::GameplayManager()
    {
        initialize();
    }

    void GameplayManager::initialize()
    {
        initializeBackgroundImage();
        initializeVariables();
    }

    void GameplayManager::initializeVariables()
    {
        board = new Board(this);
    }

    void GameplayManager::initializeBackgroundImage() {
        if (!background_texture.loadFromFile(background_texture_path)) {
            std::cerr << "Failed to load background texture!" << std::endl;
        }
        background_sprite.setTexture(background_texture);
        background_sprite.setColor(sf::Color(255, 255, 255, background_alpha));
    }

    void GameplayManager::update(EventPollingManager& eventManager, sf::RenderWindow& window)
    {
        board->update(eventManager, window);
    }

    void GameplayManager::setGameResult(GameResult gameResult)
    {
        this->game_result = gameResult;
    }

    void GameplayManager::render(sf::RenderWindow& window)
    {
        window.draw(background_sprite);
        board->render(window);
    }
}