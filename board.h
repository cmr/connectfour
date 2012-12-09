#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace Board {
	const int Y_SIZE = 6;
	const int X_SIZE = 7;

	enum Token {
		Empty,
		Red,
		Yellow
	};

	enum Outline {
		Normal,
		Highlight
	};

	enum Move {
		Placed,
		Full,
		EndOfGame
	};

	class Board {
		public:
			Board(sf::RenderWindow& app);
			~Board();

			void restart();
			void draw();
			Move addTokenInColumn(unsigned int column, Token playerColor);
			int getWindowWidth();
			sf::Color boardColor;

		private:
			bool isEndOfGame(unsigned int x, unsigned int y);
			bool fourHorizontal(unsigned int x, unsigned int y);
			bool fourVertical(unsigned int x, unsigned int y);
			bool fourDiagonal(unsigned int x, unsigned int y);

			Token board[Y_SIZE+2][X_SIZE +2];
			Outline boardOutline[Y_SIZE+2][X_SIZE+2];

			sf::RenderWindow& myWindow;

			sf::Color redColor;
			sf::Color yellowColor;
			sf::Color emptyColor;
			sf::Color lineColor;
			sf::Color highlightColor;

			float windowHeight;
			float windowWidth;

			float outline;
			float radius;

			float spaceX, spaceY;
	};
}
