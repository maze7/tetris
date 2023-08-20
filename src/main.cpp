#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "pch.h"
#include "core/game.h"

int main(int argc, char* argv[]) {

	Game game;

	auto prev = std::chrono::high_resolution_clock::now();

	while (!game.should_exit()) {
		// calculate delta time for frame
		auto now = std::chrono::high_resolution_clock::now();
		auto delta = std::chrono::duration<float, std::chrono::seconds::period>(now - prev).count();

		game.update(delta);
		game.draw();

		// update timings
		prev = now;
	}

	return 0;
}