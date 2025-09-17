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
        initializeVariables();
        createBoard();
        populateBoard();
    }

    void Board::update(Event::EventPollingManager& eventManager, sf::RenderWindow& window)
    {
        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                cell[row][col]->update(eventManager, window);
    }

    void Board::createBoard()
    {
        float cell_width = getCellWidthInBoard();
        float cell_height = getCellHeightInBoard();

        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                cell[row][col] = new Cell(cell_width, cell_height, sf::Vector2i(row, col), this); //pass the board as a parameter
    }

    void Board::onCellButtonClicked(sf::Vector2i cell_position, MouseButtonType mouse_button_type) {
        if (mouse_button_type == MouseButtonType::LEFT_MOUSE_BUTTON) {
            Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK); //play click sound
            openCell(cell_position); // Open the cell when left-clicked
        }
        else if (mouse_button_type == MouseButtonType::RIGHT_MOUSE_BUTTON)
        {
            Sound::SoundManager::PlaySound(Sound::SoundType::FLAG);//play flag sound
            toggleFlag(cell_position);
        }
    }

    void Board::toggleFlag(sf::Vector2i cell_position) {
        // get previous state
        CellState prev = cell[cell_position.x][cell_position.y]->getCellState();

        // only toggle if currently hidden or flagged
        cell[cell_position.x][cell_position.y]->toggleFlag();

        CellState now = cell[cell_position.x][cell_position.y]->getCellState();
        if (prev != now) {
            if (now == CellState::FLAGGED) ++flaggedCells;
            else if (prev == CellState::FLAGGED && now == CellState::HIDDEN) --flaggedCells;
        }
    }

    void Board::openCell(sf::Vector2i cell_position) 
    {
        if (!cell[cell_position.x][cell_position.y]->canOpenCell()) 
        {
            return; // Can't open this cell!
        }
        //cell[cell_position.x][cell_position.y]->open(); // Open it!
        processCellType(cell_position);
    }

    void Board::processCellType(sf::Vector2i cell_position) {
        switch (cell[cell_position.x][cell_position.y]->getCellType()) {
        case CellType::EMPTY:
            processEmptyCell(cell_position);
            break;
        case CellType::MINE:
            cell[cell_position.x][cell_position.y]->open();
            //Handling Mine cell in next lesson
            break;
        default:
            cell[cell_position.x][cell_position.y]->open();
            break;
        }
    }

    void Board::processEmptyCell(sf::Vector2i cell_position) {
        // First, open the current cell so neighbors won't re-open it and cause cycles.
        cell[cell_position.x][cell_position.y]->open();

        // Check all 8 neighbors
        for (int a = -1; a <= 1; ++a) {
            for (int b = -1; b <= 1; ++b) {
                // Skip the current cell
                if (a == 0 && b == 0) continue;

                //Store neighbor cells position
                sf::Vector2i next_cell_position(cell_position.x + a, cell_position.y + b);

                if (!isValidCellPosition(next_cell_position)) {
                    continue;  // Skip invalid positions
                }

                // If neighbor is flagged, unflag it (if that's intended behavior)
                CellState next_cell_state = cell[next_cell_position.x][next_cell_position.y]->getCellState();
                if (next_cell_state == CellState::FLAGGED) {
                    toggleFlag(next_cell_position);
                }

                // Open neighbor cell if allowed
                if (cell[next_cell_position.x][next_cell_position.y]->canOpenCell()) {
                    openCell(next_cell_position);
                }
            }
        }
    }

    void Board::initializeVariables()
    {
        randomEngine.seed(randomDevice()); // init random engine
        flaggedCells = 0;                   // IMPORTANT: initialize counters
    }

    void Board::populateBoard()
    {
        populateMines();
        populateCells();
    }

    void Board::populateCells()
    {
        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                if (cell[row][col]->getCellType() != CellType::MINE)
                {
                    int mines_around = countMinesAround(sf::Vector2i(row, col));
                    cell[row][col]->setCellType(static_cast<CellType>(mines_around));
                }
    }

    void Board::populateMines()
    {
        // First index is row, second index is column
        std::uniform_int_distribution<int> row_dist(0, numberOfRows - 1);
        std::uniform_int_distribution<int> col_dist(0, numberOfColumns - 1);
        int mines_placed = 0;

        while (mines_placed < minesCount)
        {
            int r = row_dist(randomEngine);
            int c = col_dist(randomEngine);

            if (cell[r][c]->getCellType() != CellType::MINE)
            {
                cell[r][c]->setCellType(CellType::MINE);
                ++mines_placed;
            }
        }
    }

    int Board::countMinesAround(sf::Vector2i cell_position)
    {
        int mines_around = 0;

        for (int a = -1; a <= 1; ++a) {
            for (int b = -1; b <= 1; ++b) {
                // Validate cell's postion and check current cell
                if ((a == 0 && b == 0) ||
                    !isValidCellPosition(sf::Vector2i(cell_position.x + a, cell_position.y + b)))
                    continue;

                //Check Mines
                if (cell[cell_position.x + a][cell_position.y + b]->getCellType() ==
                    CellType::MINE)
                    mines_around++;
            }
        }
        return mines_around;
    }

    bool Board::isValidCellPosition(sf::Vector2i cell_position)
    {
        return (cell_position.x >= 0 && cell_position.y >= 0 &&
            cell_position.x < numberOfRows && cell_position.y < numberOfColumns);
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

        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                cell[row][col]->render(window);
    }
}