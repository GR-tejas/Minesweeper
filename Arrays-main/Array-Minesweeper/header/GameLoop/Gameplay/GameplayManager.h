#pragma once
#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../../header/Time/TimeManager.h"
#include "../../header/UI/GameplayUI/GameplayUI.h"
#include <SFML/Graphics.hpp>



namespace Gameplay
{
    using namespace UI;
    using namespace Event;
    using namespace Time;

    enum class GameResult
    {
        NONE,
        WON,
        LOST
    };

    class GameplayManager
    {
    private:
        Board* board;
        GameplayUI* gameplay_ui;

        void initialize();
        void initializeVariables();
        void initializeBackgroundImage();
        bool hasGameEnded();
        void checkGameWin();
        void processGameResult();
        void gameWon();
        void gameLost();
        int getRemainingMinesCount() const;

        void updateRemainingTime();
        void processTimeOver();

        void handleGameplay(EventPollingManager& eventManager, sf::RenderWindow& window);

        const float background_alpha = 85.f;

        sf::Texture background_texture;
        sf::Sprite background_sprite;
        std::string background_texture_path = "assets/textures/minesweeper_bg.png";
        GameResult game_result;

        const float max_level_duration = 150.0f;
        const float game_over_time = 11.0f;
        float remaining_time;

    public:
        GameplayManager();
        ~GameplayManager() = default;
        void update(EventPollingManager& eventManager, sf::RenderWindow& window);
        void setGameResult(GameResult gameResult);

        void render(sf::RenderWindow& window);
    };
}