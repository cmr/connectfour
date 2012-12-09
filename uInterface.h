#pragma once

#include "board.h"

class UInterface {
	public:
		UInterface(Board::Board& boardRef);
		~UInterface();

		void placeInColumn(sf::Event::MouseButtonEvent &event);

	private:
		unsigned int column;
		Board::Board &board;
		int nbTurns;
		Board::Token nextPlayer;
		Board::Move gameStatus;
};
