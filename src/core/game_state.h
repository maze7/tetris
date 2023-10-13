#pragma once

class Game;

/**
 * GameState represents a single execution state the program can exist in; ie: MENU_STATE, PLAY_STATE, etc
 */
class GameState
{
public:
	GameState() = delete;
	GameState(Game* game) : m_game(game) {}

	virtual ~GameState() = default;

	/**
	 * Update method which is called by the Game class that owns this state. Delta time can be used to determine the time passed
	 * between the previous frame and the current one.
	 * @param dt
	 */
	virtual void update(float dt) = 0;

	/**
	 * Draws any resources owned by this state to the screen, once per frame
	 */
	virtual void draw() = 0;

protected:
	Game* m_game;
};

/**
 * Dummy state that performs no action ~ useful for testing
 */
class DummyState : public GameState
{
public:
	DummyState() = delete;
	DummyState(Game* game) : GameState(game) {}

	void update(float dt) override {}
	void draw() override {}
};