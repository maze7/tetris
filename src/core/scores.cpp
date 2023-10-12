#include "scores.h"
#include <fstream>
#include <sstream>

std::vector<Scores::ScoreEntry> Scores::m_scores;

void Scores::load() {
	std::ifstream in(scores_file);

	if (!in)
		return;

	std::string line;
	while (std::getline(in, line)) {
		int score;
		std::string name;

		std::istringstream line_stream(line);
		if (line_stream >> score && std::getline(line_stream >> std::ws, name))
			m_scores.push_back({ score, name });

		// We only want the top 10 scores
		if (m_scores.size() > 10)
			m_scores.pop_back();
	}

	// Ensure scores are sorted
	std::sort(m_scores.rbegin(), m_scores.rend());

	in.close();
}

void Scores::save() {
	std::ofstream out(scores_file);

	if (!out)
		return;

	for (const auto& [score, name] : m_scores) {
		out << score << " " << name << "\n";
	}

	out.close();
}


void Scores::add(const std::string& name, int score) {
	if (m_scores.size() < 10 || score > m_scores.back().first) {
		m_scores.push_back({ score, name });
		std::sort(m_scores.rbegin(), m_scores.rend());

		// Ensure only top 10 scores are kept
		if (m_scores.size() > 10)
			m_scores.pop_back();
	}
}

bool Scores::is_top_10(int score) {
	return m_scores.size() < 10 || score > m_scores.back().first;
}
