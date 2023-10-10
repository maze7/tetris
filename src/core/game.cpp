#include "game.h"
#include "raylib.h"
#include "menu/menu_state.h"

Game::Game() : m_music(LoadMusicStream("res/tetris-audio.wav")) {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1280, 720, "Tetris");
	SetExitKey(KEY_NULL);

	m_current_state = std::make_unique<MenuState>(this);
}

Game::~Game() {
	CloseWindow();
	CloseAudioDevice();
}

void Game::update(float dt) {
	// The m_music file is 1:23 so it will stop and start at the end
	if (!IsMusicStreamPlaying(m_music)) {
		StopMusicStream(m_music);
		PlayMusicStream(m_music); // Restart the m_music when it's over
	}

	UpdateMusicStream(m_music);

	// Toggle mute when the "M" key is pressed
	if (IsKeyPressed(KEY_M)) {
		config().play_music = !config().play_music;
		SetMusicVolume(m_music, config().play_music ? 1.0 : 0.0);
	}

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
