#include "../../header/GameLoop/Gameplay/Cell.h"

namespace Gameplay
{
	Cell::Cell(float width, float height, sf::Vector2i position)
	{
		initialize(width, height, position);
	}

	void Cell::initialize(float width, float height, sf::Vector2i position) 
	{
		this->position = position;
		sf::Vector2f cellScreenPosition = getCellScreenPosition(width, height);
		cell_button = new Button(cell_texture_path, cellScreenPosition, width * slice_count, height);
		current_cell_state = CellState::OPEN; // Temporarily set to OPEN for visualization
	}

	sf::Vector2f Cell::getCellScreenPosition(float width, float height) const
	{
		float xScreenPosition = cell_left_offset + position.x * width;
		float yScreenPosition = cell_top_offset + position.y * height;
		return sf::Vector2f(xScreenPosition, yScreenPosition);
	}


	void Cell::setCellTexture()
	{
		int index = static_cast<int>(cell_type);

		switch (current_cell_state)
		{
			//OPEN state
		case CellState::OPEN:
			cell_button->setTextureRect(sf::IntRect(index * tile_size, 0, tile_size, tile_size));
			break;
		case CellState::HIDDEN:
			cell_button->setTextureRect(sf::IntRect(10 * tile_size, 0, tile_size, tile_size));
			break;
		case CellState::FLAGGED:
			cell_button->setTextureRect(sf::IntRect(11 * tile_size, 0, tile_size, tile_size));
			break;
		}
	}

	void Cell::render(sf::RenderWindow& window) 
	{
		setCellTexture();

		if (cell_button)
			cell_button->render(window);
	}

	CellState Cell::getCellState() const { return current_cell_state; }

	void Cell::setCellState(CellState state) { current_cell_state = state; }

	CellType Cell::getCellType() const { return cell_type; }

	void Cell::setCellType(CellType type) { cell_type = type; }
}