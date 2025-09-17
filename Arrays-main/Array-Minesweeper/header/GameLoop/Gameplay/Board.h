#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/Event/EventPollingManager.h"

namespace Gameplay
{
    class GameplayManager;

    enum class BoardState
    {
        FIRST_CELL,
        PLAYING,
        COMPLETED,
    };

    class Board
    {
    private:
        GameplayManager* gameplay_manager;
        BoardState boardState;

        std::default_random_engine randomEngine;
        std::random_device randomDevice;
        
        const float boardWidth = 866.f;
        const float boardHeight = 1080.f;
        const float boardPosition = 530.f;

        static const int numberOfRows = 9;
        static const int numberOfColumns = 9;

        const float horizontalCellPadding = 115.f;
        const float verticalCellPadding = 329.f;

        int flaggedCells;

        static const int minesCount = 9;

        const std::string boardTexturePath = "assets/textures/board.png";
        sf::Texture boardTexture;
        sf::Sprite boardSprite;

        Cell* cell[numberOfRows][numberOfColumns];

        int countMinesAround(sf::Vector2i cell_position);
        void populateCells();
        bool isValidCellPosition(sf::Vector2i cell_position);

        bool isInvalidMinePosition(sf::Vector2i first_cell_position, int x, int y);

        void initializeBoardImage();
        void initialize(GameplayManager* gameplayManager);
        void initializeVariables(GameplayManager* gameplay_manager);
        void createBoard();

        float getCellWidthInBoard() const;
        float getCellHeightInBoard() const;

        void toggleFlag(sf::Vector2i cell_position);

        void populateBoard(sf::Vector2i cell_position);
        void populateMines(sf::Vector2i first_cell_position);

        void openCell(sf::Vector2i cell_position);
        void processCellType(sf::Vector2i cell_position);
        void processEmptyCell(sf::Vector2i cell_position);
        void processMineCell(sf::Vector2i cell_position);

    public:

        Board(GameplayManager* gameplayManager);
        bool areAllCellsOpen();
        void flagAllMines();
        void update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
        void onCellButtonClicked(sf::Vector2i cell_position, MouseButtonType mouse_button_type);
        void revealAllMines();
        BoardState getBoardState() const;
        void setBoardState(BoardState state);

        void render(sf::RenderWindow& window);
    };
}