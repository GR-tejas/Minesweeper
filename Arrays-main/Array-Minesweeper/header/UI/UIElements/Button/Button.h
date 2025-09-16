#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Sound/SoundManager.h"
#include <functional>

namespace UIElements {

    enum class MouseButtonType
    {
        LEFT_MOUSE_BUTTON,
        RIGHT_MOUSE_BUTTON
    };

    class Button {
    private:
        sf::Texture button_texture;
        sf::Sprite buttonSprite;

        void initialize(const std::string& texture_path, const sf::Vector2f& position, float width, float height);

    public:
        Button(const std::string& texture_path, const sf::Vector2f& position, float width, float height);

        void render(sf::RenderWindow& window) const;
    };
}