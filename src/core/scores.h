#pragma once

#include <string>
#include <vector>

class Scores
{
public:
	constexpr static const char* scores_file = "res/scores.txt";

	static void load();
	static void save();

	[[nodiscard]] static const auto& scores() { return m_scores; }
	[[nodiscard]] static bool is_top_10(int score);

	static void add(const std::string& player, int score);

private:
	using ScoreEntry = std::pair<int, std::string>;

	static std::vector<ScoreEntry> m_scores;
};