#include "pch.h"
#include "raylib.h"

int main(int argc, char* argv[])
{
	InitWindow(800, 600, "tetris");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(Color(0, 0, 0, 0));
		DrawText("Hello tetris!", 32, 32, 20, WHITE);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}