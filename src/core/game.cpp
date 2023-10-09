#include "game.h"
#include "raylib.h"
#include "menu/menu_state.h"

Game::Game() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1280, 720, "Tetris");
	SetExitKey(KEY_NULL);

	m_current_state = std::make_unique<MenuState>(this);
}

Game::~Game() {
	CloseWindow();
}

void Game::update(float dt) {
	m_current_state->update(dt);
}

void Game::draw() {
	// clear backbuffer for drawing
	BeginDrawing();
	ClearBackground(BLACK);

	// draw current game state
	m_current_state->draw();

	// swap buffers
	EndDrawing();
}

Config& Game::config() {
	return m_config;
}

bool Game::should_exit() const {
	return exit_requested || WindowShouldClose();
}

void Game::set_state(std::unique_ptr<GameState> new_state) {
	m_current_state = std::move(new_state);
}
