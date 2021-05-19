#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

class Settings
{
public:
	static constexpr int PLAYER_INITIAL_CASH = 10050;
	static constexpr int FLOWER_COST = 50;
	static constexpr int FLOWER_INCOME = 5;
	static constexpr int FLOWER_TIME_TO_GROW = 5;
	static constexpr int COIN_SPAWN_INTERVAL = 5;
	static constexpr int BONUS_SPEED_DURATION = 5;
	static constexpr int BONUS_SPEED_MULTIPLIER = 2;
	static constexpr float SNAKE_SPAWN_INTERVAL = 5.0f;
	static constexpr int SNAKE_SPAWN_INTERVAL_MODIFIER = 50;
	static constexpr int SNAKE_SPAWN_INTERVAL_MODIFICATION_INTERVAL = 10;
	static constexpr int SNAKE_MAX_LENGTH = 5;
	static constexpr int SNAKE_MAX_LENGTH_MULTIPLIER = 2;
	inline static const std::string PLAYER_NAME = "TommyKiller";

	inline static int SNAKE_MOVEMENT_SPEED = 20;
};

#endif // !SETTINGS_H
