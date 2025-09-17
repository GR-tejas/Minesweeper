#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/Event/EventPollingManager.h"

namespace Gameplay
{
    class Board
    {
    private:
        std::default_random_engine randomEngine;
        std::random_device randomDevice;
        
        const float boardWidth = 866.f;
        const float boardHeight = 1080.f;
        const float boardPosition = 530.f;

        static const int numberOfRows = 9;
        static const int numberOfColumns = 9;

        const float horizontalCellPadding = 115.f;
        const float verticalCellPadding = 329.f;

        static const int minesCount = 9;

        const std::string boardTexturePath = "assets/textures/board.png";
        sf::Texture boardTexture;
        sf::Sprite boardSprite;

        Cell* cell[numberOfRows][numberOfColumns];

        int countMinesAround(sf::Vector2i cell_position);
        void populateCells();
        bool isValidCellPosition(sf::Vector2i cell_position);

        void initializeBoardImage();
        void initialize();
        void createBoard();

        float getCellWidthInBoard() const;
        float getCellHeightInBoard() const;

        void populateBoard();
        void populateMines();

        void initializeVariables();

    public:

        Board();
        void update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void onCellButtonClicked(sf::Vector2i cell_position, MouseButtonType mouse_button_type);

        void render(sf::RenderWindow& window);
    };
}