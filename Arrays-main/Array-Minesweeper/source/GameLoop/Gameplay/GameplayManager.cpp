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
        else if (board->getBoardState() != BoardState::COMPLETED)
            processGameResult();  // Handle win/loss
    }
    bool GameplayManager::hasGameEnded()
    {
        return game_result != GameResult::NONE;
    }

    void GameplayManager::handleGameplay(EventPollingManager& eventManager, sf::RenderWindow& window) {
        updateRemainingTime();
        board->update(eventManager, window);
        checkGameWin();  // See if player has won
    }

    void GameplayManager::checkGameWin() {
        if (board->areAllCellsOpen()) {
            game_result = GameResult::WON;  // Victory!
        }
    }

    void GameplayManager::processGameResult() {
        switch (game_result) {
        case GameResult::WON:
            gameWon();
            break;
        case GameResult::LOST:
            gameLost();
            break;
        default:
            break;
        }
    }

    void GameplayManager::gameLost() {
        Sound::SoundManager::PlaySound(Sound::SoundType::EXPLOSION);  // Boom!
        board->setBoardState(BoardState::COMPLETED);  // Game over
        board->revealAllMines();  // Show where the mines were
    }

    void GameplayManager::gameWon() {
        Sound::SoundManager::PlaySound(Sound::SoundType::GAME_WON);  // Play victory sound
        board->flagAllMines();  // Show all mines
        board->setBoardState(BoardState::COMPLETED);  // Stop the game
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
        std::cout << "before setting", game_result, "\n";
        this->game_result = gameResult;
        std::cout << "after setting", game_result, "\n";
    }

    void GameplayManager::render(sf::RenderWindow& window)
    {
        window.draw(background_sprite);
        board->render(window);
    }
}