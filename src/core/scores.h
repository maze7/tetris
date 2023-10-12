#pragma once

#include <string>
#include <map>

class Scores
{
public:
	constexpr static const char* scores_file = "scores.txt";

	static void load();
	static void save();

	[[nodiscard]] const auto& scores() const { return m_scores; }

	void add(const std::string& player, int score);

private:
	std::map<int, std::string> m_scores;
};