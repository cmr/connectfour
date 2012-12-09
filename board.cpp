#include "board.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Board::Board::Board(sf::RenderWindow& app) : myWindow(app) {
	boardColor = sf::Color(0, 102, 153);
	redColor = sf::Color(214, 71, 0);
	yellowColor = sf::Color(235, 235, 0);
	emptyColor = sf::Color(224, 224, 224);
	lineColor = sf::Color(0, 51, 102);
	highlightColor = sf::Color(255, 153, 0);

	windowHeight = myWindow.getSize().x;
	windowWidth = myWindow.getSize().y;

	if(windowHeight < windowWidth)
		radius = windowHeight/(X_SIZE * 2.0);
	else
		radius = windowWidth/(Y_SIZE * 2.0);

	spaceY = 1.0/2.0 * radius;
	outline = 1.0/15.0 * radius;

	if(windowHeight < windowWidth) {
		radius = radius - spaceY/2.0 - outline;
		spaceX = (windowWidth-(X_SIZE * 2.0)*radius)/(X_SIZE + 1.0);
	} else {
		radius = radius - spaceX/2.0 - outline;
		spaceX = (windowWidth-(Y_SIZE*2.0)*radius)/(Y_SIZE + 1.0);
	}

	restart();
}

Board::Board::~Board(){}

void Board::Board::restart() {
	for(int y = 0; y < Y_SIZE+1; y++) {
		for(int x = 0; x < X_SIZE+1; x++) {
			board[y][x] = Empty;
			boardOutline[y][x] = Normal;
		}
	}
}

void Board::Board::draw() {
	for(int y = 1; y <= Y_SIZE; y++) {
		float centerY = (spaceY+radius)*y + radius*(y-1);

		for (int x = 1; x <= X_SIZE; x++) {
			float centerX = (spaceX+radius)*x + radius*(x-1);

			sf::Color fillColor;

			if(board[y][x] == Empty) {
				fillColor = emptyColor;
			} else if(board[y][x] == Red) {
				fillColor = redColor;
			} else {
				fillColor = yellowColor;
			}

			sf::Color outlineColor;

			if(boardOutline[y][x] == Highlight) {
				outlineColor = highlightColor;
			} else {
				outlineColor = lineColor;
			}

			sf::CircleShape circle;
			circle.setRadius(radius);
			circle.setOrigin(centerX, centerY);
			circle.setFillColor(fillColor);
			circle.setOutlineColor(outlineColor);
			circle.setOutlineThickness(outline);

			myWindow.draw(circle);
		}
	}
}

Board::Move Board::Board::addTokenInColumn(unsigned int column, Token playerColor) {
	for(int i = Y_SIZE; i > 0; i--) {
		if(board[i][column] == Empty) {
			board[i][column] = playerColor;
			if(isEndOfGame(i, column))
				return EndOfGame;
			else
				return Placed;
		}
	}
	return Full;
}

bool Board::Board::isEndOfGame(unsigned int y, unsigned int x) {
	return fourHorizontal(x, y) || fourVertical(x, y) || fourDiagonal(x, y);
}

bool Board::Board::fourHorizontal(unsigned int x, unsigned int y) {
	Token tokenColor = board[y][x];
	int cnt = 1, i;

	for(i = x + 1; board[y][i] == tokenColor; i++) {
		cnt++;
	}
	for(i = x - 1; board[y][i] == tokenColor; i--) {
		cnt++;
	}

	if(cnt >= 4) {
		while(board[y][++i] == tokenColor) {
			boardOutline[y][i] = Highlight;
		}
	} else {
		return false;
	}
}

bool Board::Board::fourVertical(unsigned int x, unsigned int y) {
	Token tokenColor = board[y][x];
	int cnt = 1, i;

	for(i = y+ 1; board[i][x] == tokenColor; i++)
		cnt++;
	for(i = y -1; board[i][x] == tokenColor; i--)
		cnt++;

	if(cnt >= 4) {
		while(board[++i][x] == tokenColor) {
			boardOutline[i][x] = Highlight;
		}
		return true;
	} else {
		return false;
	}
}

bool Board::Board::fourDiagonal(unsigned int x, unsigned int y) {
	Token tokenColor = board[y][x];
	bool t = false;
	int cnt = 1, i, j;

	for(i = y + 1, j = x - 1; board[i][j] == tokenColor; i++, j--)
		cnt++;
	for(i = y - 1, j = x + 1; board[i][j] == tokenColor; i--, j++)
		cnt++;

	if (cnt >= 4) {
		while(board[++i][--j] == tokenColor) {
			boardOutline[i][j] = Highlight;
		}
		t = true;
	}

	cnt = 1;

	for(i = y + 1, j = x + 1; board[i][j] == tokenColor; i++, j++)
		cnt++;
	for(i = y - 1, j = x  - 1; board[i][j] == tokenColor; i--, j--)
		cnt++;

	if(cnt >= 4) {
		while(board[++i][++j] == tokenColor) {
			boardOutline[i][j] = Highlight;;
		}
		return true;
	} else {
		return t;
	}
}

int Board::Board::getWindowWidth() {
	return myWindow.getSize().x;
}
