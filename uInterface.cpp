#include "uInterface.h"

UInterface::UInterface(Board::Board &boardRef) : board(boardRef) {
	nbTurns = 0;
	nextPlayer = Board::Yellow;
}

UInterface::~UInterface(){}

void UInterface::placeInColumn(sf::Event::MouseButtonEvent &event) {
	column = float(event.x) / board.getWindowWidth() * Board::X_SIZE + 1;

	if(gameStatus == Board::EndOfGame) {
		board.restart();
		nbTurns = 0;
		gameStatus = Board::Full;
	} else {
		gameStatus = board.addTokenInColumn(column, nextPlayer);
		if(gameStatus != Board::Full) {
			nbTurns++;
			nextPlayer = nextPlayer == Board::Yellow ? Board::Red : Board::Yellow;
			if(nbTurns == Board::X_SIZE * Board::Y_SIZE)
				gameStatus = Board::EndOfGame;
		}
	}
}

