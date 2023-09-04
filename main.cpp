#include <iostream>
#include <SFML/Graphics.hpp>

const int gridSize = 3; // Number of rows and columns in the grid
const int cellSize = 350 / gridSize; // Size of each cell
char grid[gridSize][gridSize] = {0}; // Initialize the grid with empty cells

void drawBoard(sf::RenderWindow &window, int posX, int posY, int width, int height) {
	// Draw the outline
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setPosition(posX, posY);
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(2);
	window.draw(rectangle);

	for (int i = 1; i < gridSize; ++i) {
		// Horizontal line
		sf::VertexArray hLine(sf::Lines, 2);
		hLine[0].position = sf::Vector2f(posX, posY + i * cellSize);
		hLine[1].position = sf::Vector2f(posX + width, posY + i * cellSize);
		window.draw(hLine);

		// Vertical line
		sf::VertexArray vLine(sf::Lines, 2);
		vLine[0].position = sf::Vector2f(posX + i * cellSize, posY);
		vLine[1].position = sf::Vector2f(posX + i * cellSize, posY + height);
		window.draw(vLine);
	}

	// Draw X's and O's based on the grid state
	sf::Font font;
	if (font.loadFromFile("/Users/demirelmas/Stuff/Coding/TIC-TAC-TOE/Arial.ttf")) {
		for (int x = 0; x < gridSize; ++x) {
			for (int y = 0; y < gridSize; ++y) {
				if (grid[x][y] == 'X' || grid[x][y] == 'O') {
					sf::Text symbol(grid[x][y], font, 100);
					symbol.setFillColor(sf::Color::White);
					symbol.setPosition(posX + x * cellSize + 25, posY + y * cellSize - 10);
					window.draw(symbol);
				}
			}
		}
	}
}

void handleMouseClick(sf::RenderWindow &window, int posX, int posY, int width, int height, char &currentPlayer) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	// Check if the click is in the Tic-Tac-Toe board
	if (mousePosition.x >= posX && mousePosition.x <= posX + width && mousePosition.y >= posY && mousePosition.y <= posY + height) {
		int boxX = (mousePosition.x - posX) / cellSize;
		int boxY = (mousePosition.y - posY) / cellSize;

		// Check if the cell is empty
		if (grid[boxX][boxY] == 0) {
			grid[boxX][boxY] = currentPlayer;

			// Toggle the current player (X or O)
			currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
		}
	}
}

int main() {
	// Create a window
	sf::RenderWindow window(sf::VideoMode(500, 500), "Tic-Tac-Toe");

	int posX = 75;
	int posY = 75;
	int width = 350;
	int height = 350;

	char currentPlayer = 'X'; // Starting player (X or O)

	// Main game loop
	while (window.isOpen()) {
		window.clear();
		drawBoard(window, posX, posY, width, height);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
		} else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					handleMouseClick(window, posX, posY, width, height, currentPlayer);
				}
			}
		}
		// Display everything on the window
		window.display();
	}

	return 0;
}

