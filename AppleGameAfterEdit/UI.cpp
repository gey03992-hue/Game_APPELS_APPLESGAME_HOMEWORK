#include "UI.h"
#include "Game.h"
#include <random>
namespace ApplesGame
{

	void InitHighScoreTable(UIState& uiState)
	{
		uiState.highScoreTable.clear();
		const std::vector<std::string> names = { "Alex", "Stephen", "Mickle", "John", "Tom", "Jerry" };
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> scoreDist(5, 50);

		for (int i = 0; i < MAX_HIGHSCORE_ENTRIES - 1; ++i)
		{
			uiState.highScoreTable.push_back({
				names[gen() % names.size()],
				scoreDist(gen)
				});
		}
		uiState.highScoreTable.push_back({ PLAYER_NAME, 0 }); // Добавляем игрока
		std::sort(uiState.highScoreTable.begin(), uiState.highScoreTable.end(),
			[](const auto& a, const auto& b) { return a.score > b.score; });
	}

	void UpdateHighScoreTable(UIState& uiState, const Game& game)
	{
		auto it = std::find_if(uiState.highScoreTable.begin(), uiState.highScoreTable.end(),
			[](const auto& entry) { return entry.name == PLAYER_NAME; });

		if (it != uiState.highScoreTable.end())
		{
			it->score = game.numEatenApples;
			std::sort(uiState.highScoreTable.begin(), uiState.highScoreTable.end(),
				[](const auto& a, const auto& b) { return a.score > b.score; });
		}
		else
		{
			uiState.highScoreTable.push_back({ PLAYER_NAME, game.numEatenApples });
		}

		std::sort(uiState.highScoreTable.begin(), uiState.highScoreTable.end(),
			[](const auto& a, const auto& b) { return a.score > b.score; });

		if (uiState.highScoreTable.size() > MAX_HIGHSCORE_ENTRIES)
		{
			uiState.highScoreTable.resize(MAX_HIGHSCORE_ENTRIES);
		}
	}

	void DrawHighScoreTable(UIState& uiState, sf::RenderWindow& window)
	{
		std::string tableStr = "High Scores:\n";
		for (const auto& entry : uiState.highScoreTable)
		{
			tableStr += entry.name + ": " + std::to_string(entry.score) + "\n";
		}
		uiState.highScoreText.setString(tableStr);
		window.draw(uiState.highScoreText);
	}

	void InitUI(UIState& uiState, const sf::Font& font)
	{
		// Init score text
		uiState.scoreText.setFont(font);
		uiState.scoreText.setCharacterSize(24);
		uiState.scoreText.setFillColor(sf::Color::Yellow);

		// Init hint text
		uiState.inputHintText.setFont(font);
		uiState.inputHintText.setCharacterSize(24);
		uiState.inputHintText.setFillColor(sf::Color::White);
		uiState.inputHintText.setString("Use WASD to move, ESC to exit");
		SetTextRelativeOrigin(uiState.inputHintText, 1.f, 0.f);

		// Init game over text
		//uiState.isGameOverTextVisible = false;
		uiState.gameOverText.setFont(font);
		uiState.gameOverText.setCharacterSize(144);
		uiState.gameOverText.setStyle(sf::Text::Bold);
		uiState.gameOverText.setFillColor(sf::Color::Red);
		uiState.gameOverText.setString("GAME OVER");
		SetTextRelativeOrigin(uiState.gameOverText, 0.5f, 0.5f);

		uiState.inputHintTextGameOver.setFont(font);
		uiState.inputHintTextGameOver.setCharacterSize(24);
		uiState.inputHintTextGameOver.setFillColor(sf::Color::Red);
		uiState.inputHintTextGameOver.setString("Use Space to restart game");
		SetTextRelativeOrigin(uiState.inputHintText, 1.f, 0.f);

		// Init start menu text
		uiState.firtsOptionInfo = "Off";
		uiState.secondOptionInfo = "Off";
		//uiState.isStartGameTextVisible = true;
		uiState.startHintText.setFont(font);
		uiState.startHintText.setCharacterSize(24);
		uiState.startHintText.setFillColor(sf::Color::White);
		// Init UI scoreTable
		uiState.highScoreText.setFont(font);
		uiState.highScoreText.setCharacterSize(20);
		uiState.highScoreText.setFillColor(sf::Color::White);
		uiState.highScoreText.setPosition(SCREEN_WIDTH - 200.f, 50.f);
		InitHighScoreTable(uiState);

	}

	void UpdateUIMainMenu(UIState& uiState, const Game& game, float deltaTime)
	{
		uiState.startHintText.setString("Use:\nNum1/2(on/off) - Limited apples mode - " + uiState.firtsOptionInfo + "\nNum3/4(on/off) - Accelerated movement mode - " + uiState.secondOptionInfo + "\nSpace - start game\nESC to exit");
	}

	void UpdateUIGame(UIState& uiState, const Game& game, float deltaTime)
	{
		uiState.scoreText.setString("Apples eaten: " + std::to_string(game.numEatenApples));
	}

	void DrawUI(UIState& uiState, Game& game, sf::RenderWindow& window)
	{
		switch (game.gameState)
		{
		case StateGame::MainMenu:
		{
		uiState.startHintText.setPosition(10.f, 10.f);
		DrawHighScoreTable(uiState, window);
		window.draw(uiState.startHintText);
		break;
		}
		case StateGame::PlayGame:
		{
		uiState.scoreText.setPosition(10.f, 10.f);
		window.draw(uiState.scoreText);

		uiState.inputHintText.setPosition(window.getSize().x - 10.f, 10.f);
		window.draw(uiState.inputHintText);
		break;
		}
		case StateGame::EndGame:
		{
		uiState.gameOverText.setPosition(window.getSize().x / 2.f, window.getSize().y / 1.5f);
		window.draw(uiState.gameOverText);
		window.draw(uiState.inputHintTextGameOver);
		DrawHighScoreTable(uiState, window);
		break;
		}
		}
	}
}