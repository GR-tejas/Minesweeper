#pragma once
#include <SFML/Graphics.hpp>

namespace GameWindow
{
	class GameWindowManager
	{
	private:
		const int frame_rate = 60;
		const std::string game_window_title = "Outscal Presents - Minesweeper";

		const int game_window_width = 1920;
		const int game_window_height = 1080;

		sf::RenderWindow* game_window;
		sf::VideoMode video_mode;
		const sf::Color window_color = sf::Color(200, 200, 0, 255);

		void initialize();
		sf::RenderWindow* createGameWindow();
		void setFrameRate(int);
		void configureVideoMode();
		void onDestroy();

	public:
		GameWindowManager();
		~GameWindowManager();

		bool isGameWindowOpen();
		sf::RenderWindow* getGameWindow();

		void update();
		void render();
	};
}