#include "Player.h"
#include "Game.h"

namespace ApplesGame {

	void InitPlayer(Player& player, const Game& game)
	{
		// Init player
		player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		player.playerSpeed = INITIAL_SPEED;
		player.playerDirection = PlayerDirection::Right;

		// Init player sprite
		player.sprite.setTexture(game.playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.position.x, player.position.y);

		switch (player.playerDirection)
		{
		case PlayerDirection::Up:
		{
			SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
			player.sprite.setRotation(-90.f);
			break;
		}
		case PlayerDirection::Right:
		{
			SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
			player.sprite.setRotation(0.f);
			break;
		}
		case PlayerDirection::Down:
		{
			SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
			player.sprite.setRotation(90.f);
			break;
		}
		case PlayerDirection::Left:
		{
			SetSpriteSize(player.sprite, -PLAYER_SIZE, PLAYER_SIZE);
			player.sprite.setRotation(0.f);
			break;
		}
		}

		window.draw(player.sprite);
	}

	void SetPlayerDirection(Game& game, float deltaTime)
	{
		switch (game.player.playerDirection)
		{
		case PlayerDirection::Right:
		{
			game.player.position.x += game.player.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			game.player.position.y -= game.player.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			game.player.position.x -= game.player.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			game.player.position.y += game.player.playerSpeed * deltaTime;
			break;
		}
		}
	}
}