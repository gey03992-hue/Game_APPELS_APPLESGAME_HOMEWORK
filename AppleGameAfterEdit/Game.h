#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Math.h"
#include "Constants.h"
#include "Player.h"
#include "Apple.h"
#include "Stone.h"
#include "UI.h"
#include "Background.h"


namespace ApplesGame
{
	constexpr uint8_t FINITE_MODE = 0x01;
	constexpr uint8_t ENDLESS_MODE = 0x02;
	constexpr uint8_t ACCELERATION_MODE = 0x04;
	constexpr uint8_t NO_ACCELERATION_MODE = 0x08;
	constexpr uint8_t DEFAULT_MODE = ENDLESS_MODE | NO_ACCELERATION_MODE;

	enum class StateGame
	{
		MainMenu,
		PlayGame,
		EndGame,
	};

	struct Game
	{

		int numApples = (rand() % (MAX_NUM_APPLES - MIN_NUM_APPLES)) + MIN_NUM_APPLES;
		

		// Player data
		Player player;

		// Apples data
		Apple* apples = new Apple[numApples];

		// Stones data
		Stone stones[NUM_STONES];

		// UI data
		UIState uiState;

		// Background data
		Background background;

		// Global game data
		int numEatenApples = 0;
		bool isGameFinished = false;
		float gameFinishTime = 0.f;
		bool isGameMenuOpen = true;

		uint8_t gameMode = DEFAULT_MODE;
		StateGame gameState;
		

		// Resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture stoneTexture;

		sf::SoundBuffer appleEatSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;

		sf::Sound gameOverSound;
		sf::Sound appleEatSound;

		sf::Font font;
	};

	void RestartGame(Game& game);
	void InitGame(Game& game);
	void HandlerInputMainMenu(Game& game);
	void HandlerInputPlayGame(Game& game);
	void HandlerInputEndGame(Game& game);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void GameOver(Game& game);
	void InitSound(sf::SoundBuffer& soundBuffer, sf::Sound& sound, float volume);
	void PlayAppleEatSound(Game& game);
	void PlayGameOverSound(Game& game);
	void DeinitGame(Game& game);
}