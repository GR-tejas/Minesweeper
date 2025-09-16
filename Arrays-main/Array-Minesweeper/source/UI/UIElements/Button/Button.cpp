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

    void Button::render(sf::RenderWindow& window) const 
    {
        window.draw(buttonSprite);
    }
}