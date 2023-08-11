#include <game/play_state.h>
#include "menu_state.h"
#include "config_state.h"
#include "core/game.h"
#include "score_state.h"

MenuState::MenuState(Game* game) : GameState(game) {
	// load the (placeholder) tetris logo
	m_logo = LoadTexture("res/tetris_logo.png");
	m_crt_shader = LoadShader(0, "res/crt_shader.frag");
}

MenuState::~MenuState() {
	// free gpu resources
	UnloadShader(m_crt_shader);
	UnloadTexture(m_logo);
}

void MenuState::update(float dt) {
	m_time += dt;
}

void MenuState::draw() {
	int screen_width = GetScreenWidth();
	int screen_height = GetScreenHeight();

	// random logo effect
	float logo_size[] = { (float)m_logo.width, (float)m_logo.height };
	SetShaderValue(m_crt_shader, GetShaderLocation(m_crt_shader, "size"), &logo_size, SHADER_UNIFORM_VEC2);
	SetShaderValue(m_crt_shader, GetShaderLocation(m_crt_shader, "time"), &m_time, SHADER_UNIFORM_FLOAT);
	BeginShaderMode(m_crt_shader);
	DrawTexture(m_logo, screen_width/2 - m_logo.width/2, screen_height/2 - m_logo.height/2 - 100, WHITE);
	EndShaderMode();

	// main menu buttons
	if (GuiButton({ static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2), 200, 50}, "PLAY")) {
		m_game->set_state(std::make_unique<PlayState>(m_game));
	}

	if (GuiButton({ static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2 + 60), 200, 50}, "SCORES")) {
		m_game->set_state(std::make_unique<DummyState>(m_game));
	}
	
	if (GuiButton({ static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2 + 120), 200, 50}, "CONFIGURE")) {
		m_game->set_state(std::make_unique<ConfigState>(m_game));
	}

	GuiButton({ static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2 + 180), 200, 50}, "EXIT");
}