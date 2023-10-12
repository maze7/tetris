#include <game/play_state.h>
#include "menu_state.h"
#include "config_state.h"
#include "core/game.h"
#include "score_state.h"

MenuState::MenuState(Game* game) : GameState(game) {
	// load the (placeholder) tetris logo
	m_logo = LoadTexture("res/tetris_logo.png");
}

MenuState::~MenuState() {
	UnloadTexture(m_logo);
}

void MenuState::update(float dt) {
	m_time += dt;
}

void MenuState::draw() {
	int screen_width = GetScreenWidth();
	int screen_height = GetScreenHeight();
	DrawTexture(m_logo, screen_width/2 - m_logo.width/2, screen_height/2 - m_logo.height/2 - 200, WHITE);

	// main menu buttons
	if (GuiButton({ static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2) -50, 200, 50}, "PLAY")) {
		m_game->set_state(std::make_unique<PlayState>(m_game));
	}

	if (GuiButton({ static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2 + 60) -50, 200, 50}, "SCORES")) {
		m_game->set_state(std::make_unique<ScoreState>(m_game));
	}
	
	if (GuiButton({ static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2 + 120) -50, 200, 50}, "CONFIGURE")) {
		m_game->set_state(std::make_unique<ConfigState>(m_game));
	}

	if (GuiButton({ static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2 + 180) -50, 200, 50}, "EXIT")){
		m_game->request_exit();
	}

	// list group members, course code and year
	DrawText("2805ICT - 2023", (screen_width/2 - MeasureText("2805ICT - 2023", 20)/2), (screen_height/2 + 275), 20, WHITE);
	DrawText("Bailey Bingham-Wilson, Callan Acton and Nathan Wilson", (screen_width/2 - MeasureText("Bailey Bingham-Wilson, Callan Acton and Nathan Wilson", 20) / 2), (screen_height / 2 + 300), 20, WHITE);
}