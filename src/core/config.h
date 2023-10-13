#pragma once

/**
 * Enum representing the current difficulty level
 */
enum class DifficultyLevel {
	Easy,
	Medium,
	Hard
};

/**
 * Enum representing the current Game Mode
 */
enum class GameMode {
	Player,
	AI,
};

/**
 * Enum representing the current game type
 */
enum class GameType {
	Normal,
	Extended
};

/**
 * State object which is responsible for managing the game configuration between screens.
 */
class Config
{
public:
	Config() = default;

	// the current game mode
	GameMode game_mode = GameMode::Player;

	// the current game type
	GameType game_type = GameType::Normal;

	// the current difficulty level
	DifficultyLevel difficulty = DifficultyLevel::Medium;

	// the current grid width
	int board_width = 10;

	// the current grid height
	int board_height = 20;

	// whether music should be muted or not
	bool play_music = true;
};