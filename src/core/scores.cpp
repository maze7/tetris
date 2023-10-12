
#include "scores.h"

void Scores::load() {

}

void Scores::save() {

}

void Scores::add(const std::string& player, int score) {
	m_scores[score] = player;
}
