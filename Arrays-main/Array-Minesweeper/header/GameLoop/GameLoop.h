#pragma once
#include "../../header/GameWindow/GameWindowManager.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/UI/SplashScreen/SplashScreenManager.h"

using namespace GameWindow;
using namespace Event;
using namespace UI;

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