#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Game.h"

void HandleWindowEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		// Close window if close button or Escape key pressed
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
		{
			window.close();
		}
	}
}

int main()
{
	using namespace ApplesGame;

	// Init seed
	int seed = (int)time(nullptr);
	srand(seed);

	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	// Game initialization
	Game game;
	InitGame(game);

	// Init game clock
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// Main loop
	while (window.isOpen())
	{
		// Reduce framerate
		sf::sleep(sf::milliseconds(15));

		// Calculate delta time
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Read events
		HandleWindowEvents(window);

		// Update game state
		UpdateGame(game, deltaTime);

		// Draw game
		window.clear();
		DrawGame(game, window);
		window.display();

	}

	// Deinitilization
	DeinitGame(game);

	return 0;
}