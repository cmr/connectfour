#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "board.h"
#include "uInterface.h"

int main() {
	unsigned int antialias = 8;

	sf::RenderWindow app(sf::VideoMode(800, 600), "Connect Four",
			sf::Style::Resize | sf::Style::Close, sf::ContextSettings(24, 8, antialias));

	app.setFramerateLimit(60);

	Board::Board board(app);
	UInterface ui(board);

	while(app.isOpen()) {
		sf::Event event;
		while(app.pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				app.close();
			} else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				ui.placeInColumn(event.mouseButton);
			}
		}

		app.clear();
		board.draw();
		app.display();
	}

	return EXIT_SUCCESS;
}
