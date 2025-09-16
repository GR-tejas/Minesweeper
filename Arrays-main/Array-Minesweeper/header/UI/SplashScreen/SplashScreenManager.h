#pragma once
#include <SFML/Graphics.hpp>

namespace UI {
    class SplashScreenManager {
    private:
        sf::RenderWindow* game_window;
        sf::Texture logo_texture;
        sf::Sprite logo_sprite;

        const float logo_width = 600.f;
        const float logo_height = 134.f;
        const float logo_animation_duration = 2.0f;
        const std::string logo_texture_path = "assets/textures/outscal_logo.png";

        float elapsed_time = 0.0f;

        void initialize();
        sf::Vector2f getLogoPosition();
        void drawLogo();

    public:
        SplashScreenManager(sf::RenderWindow* window);
        ~SplashScreenManager();

        void update();
        void render();
    };
}