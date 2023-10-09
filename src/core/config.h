#pragma once

enum class DifficultyLevel {
	Easy,
	Medium,
	Hard
};

enum class GameMode {
	Player,
	AI,
};

enum class GameType {
	Normal,
	Extended
};

class Config
{
public:
	Config() = default;

	GameMode game_mode = GameMode::Player;
	GameType game_type = GameType::Normal;
	DifficultyLevel difficulty = DifficultyLevel::Medium;

	int board_width = 10;
	int board_height = 20;
};