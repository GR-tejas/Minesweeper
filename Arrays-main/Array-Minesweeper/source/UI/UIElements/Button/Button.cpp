#include "../../header/UI/UIElements/Button/Button.h"
#include <iostream>

namespace UIElements {

    Button::Button(const std::string& texturePath, const sf::Vector2f& position, float width, float height) 
    {
        initialize(texturePath, position, width, height);
    }

    void Button::initialize(const std::string& texturePath, const sf::Vector2f& position, float width, float height) 
    {
        if (!button_texture.loadFromFile(texturePath)) 
        {
            std::cerr << "Failed to load button texture: " << texturePath << std::endl;
            return;
        }
        buttonSprite.setTexture(button_texture);
        buttonSprite.setPosition(position);
        buttonSprite.setScale(width / button_texture.getSize().x, height / button_texture.getSize().y);
    }

    void Button::registerCallbackFunction(CallbackFunction button_callback) 
    {
        callback_function = button_callback;
    }

    void Button::setTextureRect(const sf::IntRect& rect) 
    {
        //Set a rectangle on the texture
        buttonSprite.setTextureRect(rect);
    }

    bool Button::isMouseOnSprite(Event::EventPollingManager& event_manager, const sf::RenderWindow& window)
    {
        //Get the position of the mouse
        sf::Vector2i mouse_position = event_manager.getMousePosition();

        //Check if the mouse’s position is present in the bounds of buttonSprite.
        return buttonSprite.getGlobalBounds().contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));
    }

    void Button::handleButtonInteractions(Event::EventPollingManager& event_manager, const sf::RenderWindow& window) 
    {
        if (event_manager.pressedLeftMouseButton() && isMouseOnSprite(event_manager, window)) 
        {
            callback_function(MouseButtonType::LEFT_MOUSE_BUTTON);
        }
        else if (event_manager.pressedRightMouseButton() && isMouseOnSprite(event_manager, window)) 
        {
            callback_function(MouseButtonType::RIGHT_MOUSE_BUTTON);
        }
    }

    void Button::render(sf::RenderWindow& window) const 
    {
        window.draw(buttonSprite);
    }
}