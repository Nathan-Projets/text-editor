#include <print>
#include <raylib.h>

#include "../includes/label.hpp"
#include "../includes/button.hpp"

int main(int argc, char const *argv[])
{
    InitWindow(800, 450, "Text Editor");

    Label helloWorld("Hello World!");
    helloWorld.position = Vector2(50, 50);

    Button helloButton("Click on me");
    helloButton.position = Vector2(50, 100);
    helloButton.setHandlerClick([&helloButton]
                                { std::print("button {} clicked ", helloButton.getData()); });

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(MAGENTA);

        helloWorld.render();
        helloButton.render();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Vector2 mouse = GetMousePosition();
            helloButton.click();
        }

        EndDrawing();
    }

    CloseWindow();
}