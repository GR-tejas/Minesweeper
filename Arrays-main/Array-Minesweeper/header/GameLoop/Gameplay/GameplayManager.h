#pragma once
#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/Event/EventPollingManager.h"
#include <SFML/Graphics.hpp>

using namespace Event;

namespace Gameplay
{
    class GameplayManager
    {
    private:
        Board* board;

        void initialize();
        void initializeVariables();
        void initializeBackgroundImage();

        const float background_alpha = 85.f;

        sf::Texture background_texture;
        sf::Sprite background_sprite;
        std::string background_texture_path = "assets/textures/minesweeper_bg.png";

    public:
        GameplayManager();
        ~GameplayManager() = default;
        void update(EventPollingManager& eventManager, sf::RenderWindow& window);

        void render(sf::RenderWindow& window);
    };
}