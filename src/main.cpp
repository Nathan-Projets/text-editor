#include <print>
#include <raylib.h>

int main(int argc, char const *argv[])
{
    InitWindow(800, 450, "Text Editor");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(MAGENTA);
        EndDrawing();
    }

    CloseWindow();
}