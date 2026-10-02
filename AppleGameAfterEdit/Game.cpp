#include "Game.h"
#include "cassert"
#include <iostream>

namespace ApplesGame
{

	void RestartGame(Game& game)
	{
		// Init background
		InitBackground(game.background);

		// Init player
		InitPlayer(game.player, game);

		// Init apples
		for (Apple* ptr = game.apples; ptr < game.apples + game.numApples; ++ptr)
		{
			InitApple(*ptr, game);
		}

		// Init stones
		for (Stone& stone : game.stones)
		{
			InitStone(stone, game);
		}
		
			
		if (game.gameMode & FINITE_MODE)
		{
			game.numEatenApples = game.numApples;
			if (game.numEatenApples == 0)
			{
				GameOver(game);
			}
		}
		else
		{
			game.numEatenApples = 0;
		}

		game.isGameFinished = false;
		game.gameFinishTime = 0.f;
	}

	void InitGame(Game& game)
	{

		// Load textures
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(game.stoneTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));

		// Load fonts
		assert(game.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		// Load sounds
		assert(game.appleEatSoundBuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
		assert(game.gameOverSoundBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
		/*for (int i = 0; i<= NamePlauer; ++i )
		{

		}*/

		// Set audio params
		InitSound(game.gameOverSoundBuffer, game.gameOverSound, 25.f);
		InitSound(game.appleEatSoundBuffer, game.appleEatSound, 25.f);

		game.gameState = StateGame::MainMenu;

		// Init UI
		InitUI(game.uiState, game.font);

		// Random apples count
		//game.numApples = rand() % 30 + 5;

		RestartGame(game);
	}

	void HandlerInputMainMenu(Game& game)
	{
		//sf::Event event;
		if (game.gameState == StateGame::MainMenu)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				game.gameState = StateGame::PlayGame;
				RestartGame(game);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				game.uiState.firtsOptionInfo = "On";
				game.gameMode |= FINITE_MODE;
				game.gameMode &= ~ENDLESS_MODE;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				game.uiState.firtsOptionInfo = "Off";
				game.gameMode |= ENDLESS_MODE;
				game.gameMode &= ~FINITE_MODE;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				game.uiState.secondOptionInfo = "On";
				game.gameMode |= ACCELERATION_MODE;
				game.gameMode &= ~NO_ACCELERATION_MODE;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			{
				game.uiState.secondOptionInfo = "Off";
				game.gameMode |= NO_ACCELERATION_MODE;
				game.gameMode &= ~ACCELERATION_MODE;
			}
			return;
		}
	}
	void HandlerInputPlayGame(Game& game)
	{
		if (game.gameState == StateGame::PlayGame)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				game.player.playerDirection = PlayerDirection::Right;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				game.player.playerDirection = PlayerDirection::Up;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				game.player.playerDirection = PlayerDirection::Left;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				game.player.playerDirection = PlayerDirection::Down;
			}
		}
	}
	void HandlerInputEndGame(Game& game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				game.gameState = StateGame::PlayGame;
				RestartGame(game);
			}
		
	}

	void UpdateGame(Game& game, float deltaTime)
	{
		if (game.gameState == StateGame::MainMenu)
		{
			HandlerInputMainMenu(game);
			UpdateUIMainMenu(game.uiState, game, deltaTime);
		}

		else if (game.gameState == StateGame::PlayGame)
		{
			// Handler for keyboard
			HandlerInputPlayGame(game);

			// Set player's direction
			SetPlayerDirection(game, deltaTime);

			// Check stones collision
			for (Stone& stone : game.stones)
			{
				if (isRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE }, stone.position, { STONE_SIZE, STONE_SIZE }))
				{
					GameOver(game);
				}
			}

			// Check screen borders collision
			if (game.player.position.x - PLAYER_SIZE / 2.f < 0.f || game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH || game.player.position.y - PLAYER_SIZE / 2.f < 0.f || game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT) {
				GameOver(game);
			}

			// Check apples collision
			for (int i = 0; i < game.numApples; ++i) {
				if (game.apples[i].isEaten) {
					continue;
				}

				// Calculate the square of the distance
				const float dx = game.player.position.x - game.apples[i].position.x;
				const float dy = game.player.position.y - game.apples[i].position.y;
				const float distanceSq = dx * dx + dy * dy;

				// Filter by distance
				if (distanceSq > COLLISION_CHECK_RADIUS * COLLISION_CHECK_RADIUS) {
					continue;
				}

				// Accurate collision check
				if (isCirclesCollide(
					game.player.position, PLAYER_SIZE / 2.f,
					game.apples[i].position, APPLE_SIZE / 2.f))
				{
					PlayAppleEatSound(game);
					if (game.gameMode & FINITE_MODE) {
						--game.numEatenApples;
						game.apples[i].isEaten = true;
						if (game.numEatenApples == 0)
						{
							GameOver(game);
						}
						
					}
					
					else {
						++game.numEatenApples;
						game.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
					}
					if (game.gameMode & ACCELERATION_MODE) {
						game.player.playerSpeed += ACCELERATION;
					}
				}
			}

		}
		else if (game.gameState == StateGame::EndGame)
		{
			if (game.gameFinishTime <= TIMEOUT)
			{
				game.gameFinishTime += deltaTime;
				//SetBackgroundColor(game.background, sf::Color::Yellow);
				HandlerInputEndGame(game);
			}
			else
			{
				HandlerInputEndGame(game);
			}
		}
		UpdateUIGame(game.uiState, game, deltaTime);
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		if (game.gameState == StateGame::PlayGame)
		{
			// Draw background
			DrawBackground(game.background, window);

			// Draw player
			DrawPlayer(game.player, window);

			// Draw apples
			for (Apple* ptr = game.apples; ptr < game.apples + game.numApples; ++ptr)
			{
				DrawApple(*ptr, window);
			}

			// Draw stones
			for (Stone& stone : game.stones)
			{
				DrawStone(stone, window);
			}
		}
		else if (game.gameState == StateGame::EndGame)
		{
			DrawBackground(game.background, window);
		}
		DrawUI(game.uiState, game, window);
	}

	void PlayAppleEatSound(Game& game)
	{
		game.appleEatSound.play();
	}

	void PlayGameOverSound(Game& game)
	{
		game.gameOverSound.play();
	}

	void GameOver(Game& game)
	{
		PlayGameOverSound(game);
		game.gameState = StateGame::EndGame;
		game.gameFinishTime = 0.f;
		UpdateHighScoreTable(game.uiState, game);
		
	}

	void InitSound(sf::SoundBuffer& soundBuffer, sf::Sound& sound, float volume)
	{
		sound.setBuffer(soundBuffer);
		sound.setVolume(volume);
	}

	void DeinitGame(Game& game)
	{
		delete[] game.apples;
	}
}