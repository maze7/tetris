#pragma once

#include <string>
#include <vector>

/**
 * Scores is a pure-static singleton which is used to manage the top scores and current scores of the player & AIs.
 * When the program is initialized, scores loads the existing scores from disk. When the game ends, the top 10 scores are written to
 * res/scores.txt.
 */
class Scores
{
public:
	constexpr static const char* scores_file = "res/scores.txt";

	/**
	 * Loads all scores from disk (if any scores exist)
	 */
	static void load();

	/**
	 * Saves the top 10 scores to disk
	 */
	static void save();

	/**
	 * Accessor which provides access to the internal scores vector (useful for iterating the scores)
	 * @return reference to the internal scores vector
	 */
	[[nodiscard]] static const auto& scores() { return m_scores; }

	/**
	 * Determines if a given score is within the top 10 high scores.
	 * @param score the score to be checked
	 * @return true if score is in top 10, false if not
	 */
	[[nodiscard]] static bool is_top_10(int score);

	/**
	 * Adds a new entry to the scores vector
	 * @param player The name of the player that achieved the score
	 * @param score The score the player achieved
	 */
	static void add(const std::string& player, int score);

	/**
	 * Utility method which draws the top 10 scores to the screen. This is used by the ScoreState and the GameOverState classes.
	 * @param bounds The screen coordinates that the menu should be drawn within
	 */
	static void draw(Rectangle bounds);

private:
	using ScoreEntry = std::pair<int, std::string>;
	static std::vector<ScoreEntry> m_scores;
};