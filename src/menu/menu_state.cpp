#include "menu_state.h"

MenuState::MenuState() {
	// load the (placeholder) tetris logo
	m_logo = LoadTexture("res/tetris_logo.png");
	m_crt_shader = LoadShader(0, "res/crt_shader.frag");
}

MenuState::~MenuState() {
	// free the logo image from the gpu
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
	GuiButton({ static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2), 200, 50}, "PLAY");
	GuiButton({ static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2 + 75), 200, 50}, "OPTIONS");
	GuiButton({ static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2 + 150), 200, 50}, "EXIT");
}