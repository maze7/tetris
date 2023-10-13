#pragma once

#include "pch.h"
#include "game_state.h"
#include "config.h"

/**
 * The Game class is responsible for the program main loop, as well as managing the current GameState (Screen) which is being displayed.
 * This class essentially acts as the "Manager" class for the game, and is responsible for functionality that should persist across screens.
 */
class Game
{
public:
	/**
	 * Constructor
	 */
	Game();

	/**
	 * Destructor
	 */
	~Game();

	/**
	 * Performs a single 'tick' or update, using the delta time provided to move the game forward
	 * @param dt delta time
	 */
	void update(float dt);

	/**
	 * Draws the current state of the game to the screen
	 */
	void draw();

	/**
	 * Changes the current GameState to the new_state. Existing GameState is destroyed.
	 * @param new_state new state (screen) to move to
	 */
	void set_state(std::unique_ptr<GameState> new_state);

	/**
	 * Returns whether the game should exit
	 * @return true if yes, false if not
	 */
	[[nodiscard]] bool should_exit() const;

	/**
	 * Accessor to the Config struct which is responsible for managing the settings of the game.
	 * @return
	 */
	[[nodiscard]] Config& config();

	/**
	 * Accessor to the game music, which persists across screens. This is modified by the PlayState by
	 * increasing the music speed as the game gets more difficult.
	 * @return Reference to the main theme music
	 */
	[[nodiscard]] Music& music() { return m_music; }

	/**
	 * Allows a state to request the game close when possible (after freeing resources)
	 */
    void request_exit() {
        exit_requested = true;
    }

private:
	std::unique_ptr<GameState> m_current_state = nullptr;

	Texture m_sound_on, m_sound_off;
	Config m_config;
	Music m_music;

	int m_width = 0;
	int m_height = 0;

	bool exit_requested = false;
};