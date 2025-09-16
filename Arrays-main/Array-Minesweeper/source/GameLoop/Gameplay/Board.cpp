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
	}

    void Board::initializeBoardImage() {
        if (!boardTexture.loadFromFile(boardTexturePath)) {
            std::cerr << "Failed to load board texture!" << std::endl;
            return;
        }

        boardSprite.setTexture(boardTexture);
        boardSprite.setPosition(boardPosition, 0);
        boardSprite.setScale(boardWidth / boardTexture.getSize().x,
            boardHeight / boardTexture.getSize().y);
    }

    void Board::render(sf::RenderWindow& window)
    {
        window.draw(boardSprite);
    }
}