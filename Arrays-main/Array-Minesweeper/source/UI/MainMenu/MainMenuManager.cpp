#include "../../header/UI/MainMenu/MainMenuManager.h"
#include "../../../header/GameLoop/GameLoop.h"
#include <iostream>

namespace UI {
    MainMenuManager::MainMenuManager(sf::RenderWindow* window)
    {
        game_window = window;
        initialize();
    }

    MainMenuManager::~MainMenuManager()
    {
        delete play_button;
        delete quit_button;
    }

    void MainMenuManager::initialize()
    {
        initializeBackground();
        initializeButtons();
    }

    void MainMenuManager::initializeBackground() {
        if (!background_texture.loadFromFile(background_texture_path)) {
            std::cerr << "Failed to load background texture" << std::endl;
            return;
        }
        background_sprite.setTexture(background_texture);
        background_sprite.setColor(sf::Color(255, 255, 255, background_alpha));
    }

    void MainMenuManager::initializeButtons() {
        play_button = new Button(play_button_texture_path,
            getButtonPosition(0.f, play_button_y_position),
            button_width, button_height);

        quit_button = new Button(quit_button_texture_path,
            getButtonPosition(0.f, quit_button_y_position),
            button_width, button_height);

        registerButtonCallbacks();
    }

    sf::Vector2f MainMenuManager::getButtonPosition(float offsetX, float offsetY) {
        float x_position = (game_window->getSize().x - button_width) / 2.0f + offsetX;
        float y_position = offsetY;
        return sf::Vector2f(x_position, y_position);
    }

    void MainMenuManager::registerButtonCallbacks() {
        play_button->registerCallbackFunction([this](UIElements::MouseButtonType buttonType)
            {
                playButtonCallback(buttonType);
            }
        );
        quit_button->registerCallbackFunction([this](UIElements::MouseButtonType buttonType)
            {
                quitButtonCallback(buttonType);
            }
        );
    }

    void MainMenuManager::show()
    {
        game_window->draw(background_sprite);
        if (play_button) play_button->render(*game_window);
        if (quit_button) quit_button->render(*game_window);
    }

    void MainMenuManager::playButtonCallback(MouseButtonType mouse_button_type) {
        if (mouse_button_type == MouseButtonType::LEFT_MOUSE_BUTTON) {
            Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
            GameLoop::setGameState(GameState::GAMEPLAY);  // Start the game
        }
    }

    void MainMenuManager::quitButtonCallback(MouseButtonType mouse_button_type) {
        if (mouse_button_type == MouseButtonType::LEFT_MOUSE_BUTTON) {
            Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
            GameLoop::setGameState(GameState::EXIT);  // Quit the game
        }
    }

    void MainMenuManager::render() {
        game_window->draw(background_sprite);
        if (play_button) play_button->render(*game_window);
        if (quit_button) quit_button->render(*game_window);
    }

    void MainMenuManager::update(EventPollingManager eventManager) {
        play_button->handleButtonInteractions(eventManager, *game_window);
        quit_button->handleButtonInteractions(eventManager, *game_window);
    }

    void MainMenuManager::checkForButtonClicks(Event::EventPollingManager& eventManager)
    {
        if (play_button) play_button->handleButtonInteractions(eventManager, *game_window);
        if (quit_button) quit_button->handleButtonInteractions(eventManager, *game_window);
    }
}