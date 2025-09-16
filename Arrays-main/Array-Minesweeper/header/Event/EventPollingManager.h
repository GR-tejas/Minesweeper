#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace Event
{
    enum class MouseButtonState
    {
        PRESSED,
        HELD,
        RELEASED,
    };

    class EventPollingManager
    {
    private:
        sf::Event game_event;
        sf::RenderWindow* game_window;

        MouseButtonState left_mouse_button_state;
        MouseButtonState right_mouse_button_state;

        void initializeVariables(sf::RenderWindow* window);
        void updateMouseButtonState(MouseButtonState& button_state, sf::Mouse::Button button_type);

        bool hasQuitGame();
        bool isKeyboardEvent();
        bool isGameWindowOpen();
        bool gameWindowWasClosed();

    public:
        EventPollingManager(sf::RenderWindow* window);
        ~EventPollingManager();

        void processEvents();
        void update();

        bool pressedEscapeKey();
        bool pressedLeftMouseButton();
        bool pressedRightMouseButton();

        sf::Vector2i getMousePosition();
    };
}