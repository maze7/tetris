#include "game.h"
#include "raylib.h"
#include "menu/menu_state.h"

Game::Game() {
	InitWindow(800, 600, "Tetris");

	m_current_state = std::make_unique<MenuState>();
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

bool Game::should_exit() const {
	return WindowShouldClose();
}
