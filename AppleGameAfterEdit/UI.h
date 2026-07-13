#pragma once
#include "SFML/Graphics.hpp"
#include <string>

namespace ApplesGame
{
	struct HighScoreEntry
	{
		std::string name;
		int score = 0;
	};

	struct UIState
	{
		std::string firtsOptionInfo;
		std::string secondOptionInfo;

		sf::Text scoreText;
		sf::Text inputHintText;
		sf::Text gameOverText;
		sf::Text startHintText;
		sf::Text inputHintTextGameOver;
		sf::Text scoreTable;
		std::vector<HighScoreEntry> highScoreTable;
		sf::Text highScoreText;
	};

	void InitUI(UIState& uiState, const sf::Font& font);
	void UpdateUIMainMenu(UIState& uiState, const struct Game& game, float timeDelta);
	void UpdateUIGame(UIState& uiState, const struct Game& game, float timeDelta);
	void DrawUI(UIState& uiState, Game& game, sf::RenderWindow& window);
	void InitHighScoreTable(UIState& uiState);
	void UpdateHighScoreTable(UIState& uiState, const Game& game);
	void DrawHighScoreTable(const UIState& uiState, sf::RenderWindow& window);
}