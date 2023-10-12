#include "game.h"
#include "raylib.h"
#include "menu/menu_state.h"

Game::Game() : m_music(LoadMusicStream("res/tetris-audio.wav")) {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1280, 720, "Tetris");
	SetExitKey(KEY_NULL);

	m_sound_on = LoadTexture("res/sound_on.png");
	m_sound_off = LoadTexture("res/sound_off.png");
	m_current_state = std::make_unique<MenuState>(this);
}

Game::~Game() {
	UnloadTexture(m_sound_on);
	UnloadTexture(m_sound_off);
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

	// Toggle music when mute / unmute icon is pressed
	Rectangle sound_button = { (float)GetScreenWidth() - 100, (float)GetScreenHeight() - 75, (float)m_sound_on.width, (float)m_sound_on.height };
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		if (CheckCollisionPointRec(GetMousePosition(), sound_button)) {
			config().play_music = !config().play_music;
			SetMusicVolume(m_music, config().play_music ? 1.0 : 0.0);
		}
	}

	m_current_state->update(dt);
}

void Game::draw() {
	// clear back buffer for drawing
	BeginDrawing();
	ClearBackground(Color(28, 31, 94, 255));

	// Draw music mute/unmute icon (this should be visible on all screens)
	DrawTexture(config().play_music ? m_sound_on : m_sound_off, GetScreenWidth() - 100, GetScreenHeight() - 75, WHITE);

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
