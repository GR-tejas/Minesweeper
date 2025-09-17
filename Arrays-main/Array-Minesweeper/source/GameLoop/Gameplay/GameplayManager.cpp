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

    void GameplayManager::initializeVariables() {
        board = new Board(this);
        remaining_time = max_level_duration;  // Start with full time
    }

    void GameplayManager::initializeBackgroundImage() {
        if (!background_texture.loadFromFile(background_texture_path)) {
            std::cerr << "Failed to load background texture!" << std::endl;
        }
        background_sprite.setTexture(background_texture);
        background_sprite.setColor(sf::Color(255, 255, 255, background_alpha));
    }

    void GameplayManager::update(EventPollingManager& eventManager, sf::RenderWindow& window) {
        if (!hasGameEnded())
            handleGameplay(eventManager, window);
    }
    bool GameplayManager::hasGameEnded()
    {
        return false;
    }

    void GameplayManager::handleGameplay(EventPollingManager& eventManager, sf::RenderWindow& window) {
        updateRemainingTime();              // Update timer first
        board->update(eventManager, window); // Then update board
    }

    void GameplayManager::updateRemainingTime() {
        remaining_time -= TimeManager::getDeltaTime();  // Decrease time
        processTimeOver();  // Check if time's up
    }

    void GameplayManager::processTimeOver() {
        if (remaining_time <= 0) {
            remaining_time = 0; // Don't go negative
            game_result = GameResult::LOST; // Game over!
        }
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