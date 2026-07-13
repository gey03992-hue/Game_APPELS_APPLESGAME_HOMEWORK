#pragma once
#include <string>

namespace ApplesGame
{
	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const float INITIAL_SPEED = 100.f; 
	const float PLAYER_SIZE = 20.f;
	const float ACCELERATION = 20.f; 
	const int MAX_NUM_APPLES = 30;
	const int MIN_NUM_APPLES = 10;
	const float APPLE_SIZE = 20.f;
	const int NUM_STONES = 5;
	const float STONE_SIZE = 40.f;
	const float TIMEOUT = 3.f;
	const int MAX_HIGHSCORE_ENTRIES = 10;
	const std::string PLAYER_NAME = "Player";
	const float COLLISION_CHECK_RADIUS = 200.f;
}