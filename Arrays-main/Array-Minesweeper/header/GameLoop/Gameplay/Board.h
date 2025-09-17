#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/Event/EventPollingManager.h"

namespace Gameplay
{
    class Board
    {
    private:

        
        const float boardWidth = 866.f;
        const float boardHeight = 1080.f;
        const float boardPosition = 530.f;

        static const int numberOfRows = 9;
        static const int numberOfColumns = 9;

        const float horizontalCellPadding = 115.f;
        const float verticalCellPadding = 329.f;

        const std::string boardTexturePath = "assets/textures/board.png";
        sf::Texture boardTexture;
        sf::Sprite boardSprite;

        Cell* cell[numberOfRows][numberOfColumns];

        void initializeBoardImage();
        void initialize();
        void createBoard();

        float getCellWidthInBoard() const;
        float getCellHeightInBoard() const;

    public:

        Board();

        void render(sf::RenderWindow& window);
    };
}