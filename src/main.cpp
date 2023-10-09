#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "pch.h"
#include "core/game.h"

int main(int argc, char* argv[]) {

	Game game;

	auto prev = std::chrono::high_resolution_clock::now();

	InitAudioDevice();
	Music music = LoadMusicStream("res/tetris-audio.wav");
    bool mute = false;
    float volume = 1.0f;

	while (!game.should_exit()) {
		// The music file is 1:23 so it will stop and start at the end 
		if (!IsMusicStreamPlaying(music)) {
            StopMusicStream(music);
            PlayMusicStream(music); // Restart the music when it's over
        }
		UpdateMusicStream(music);
        // Toggle mute when the "M" key is pressed
        if (IsKeyPressed(KEY_M)) {
            mute = !mute;
            if (mute) {
                volume = 0.0f; // Mute volume
            } else {
                volume = 1.0f; // Unmute volume
            }
            SetMusicVolume(music, volume);
        }

		// calculate delta time for frame
		auto now = std::chrono::high_resolution_clock::now();
		auto delta = std::chrono::duration<float, std::chrono::seconds::period>(now - prev).count();

		game.update(delta);
		game.draw();

		// update timings
		prev = now;
	}

	CloseAudioDevice();
	return 0;
}