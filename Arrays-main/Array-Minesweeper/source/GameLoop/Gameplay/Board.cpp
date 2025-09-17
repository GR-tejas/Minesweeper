#include "../../header/GameLoop/Gameplay/Board.h"

namespace Gameplay
{
	Board::Board()
	{
		initialize();
	}

	void Board::initialize()
	{
		initializeBoardImage();
        createBoard();
	}

    void Board::createBoard()
    {
        float cell_width = getCellWidthInBoard();
        float cell_height = getCellHeightInBoard();
        for (int col = 0; col < numberOfColumns; ++col) {
            cell[col] = new Cell(cell_width, cell_height, sf::Vector2i(col, 0));
        }
    }

    void Board::initializeBoardImage() 
    {
        if (!boardTexture.loadFromFile(boardTexturePath)) 
        {
            std::cerr << "Failed to load board texture!" << std::endl;
            return;
        }

        boardSprite.setTexture(boardTexture);
        boardSprite.setPosition(boardPosition, 0);
        boardSprite.setScale(boardWidth / boardTexture.getSize().x,
        boardHeight / boardTexture.getSize().y);
    }

    float Board::getCellWidthInBoard() const
    {
        return (boardWidth - horizontalCellPadding) / numberOfColumns;
    }

    float Board::getCellHeightInBoard() const
    {
        return (boardHeight - verticalCellPadding) / numberOfRows;
    }


    void Board::render(sf::RenderWindow& window)
    {
        window.draw(boardSprite);
        for (int col = 0; col < numberOfColumns; ++col) {
            cell[col]->render(window);
        }
    }
}