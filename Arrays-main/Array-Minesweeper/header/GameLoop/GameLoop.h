#pragma once
#include "../../header/GameWindow/GameWindowManager.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/UI/SplashScreen/SplashScreenManager.h"
#include "../../header/GameLoop/Gameplay/GameplayManager.h"

using namespace GameWindow;
using namespace Event;
using namespace UI;
using namespace Gameplay;

enum class GameState
{
    SPLASH_SCREEN,
    MAIN_MENU,
    GAMEPLAY,
    EXIT
};

class GameLoop {
private:
    GameWindowManager* window_manager;
    EventPollingManager* event_manager;
    GameplayManager* gameplay_manager;

    sf::RenderWindow* game_window;
    SplashScreenManager* splash_screen_manager;

    static GameState current_state;

    void initialize();
    void update();
    void render();

public:
    GameLoop();
    ~GameLoop();

    void run();
    static void setGameState(GameState state_to_set);
};