#include <memory>
#include <print>

#include <raylib.h>

#include "../includes/application.hpp"
#include "../includes/container.hpp"
#include "../includes/panel.hpp"
#include "../includes/label.hpp"
#include "../includes/button.hpp"
#include "../includes/colors.hpp"

int main(int argc, char const *argv[])
{
    std::unique_ptr<Label> helloWorld = std::make_unique<Label>("Hello World!");

    std::unique_ptr<Button> helloButton = std::make_unique<Button>("Click on me");
    helloButton->setPadding(Vector2(10, 15));
    helloButton->setHandlerClick([]
                                 { std::print("button clicked"); });

    std::unique_ptr<Panel> root = std::make_unique<Panel>("Left panel", Direction::VERTICAL);
    root->add(std::move(helloWorld));
    root->add(std::move(helloButton));

    std::unique_ptr<Window> mainwindow = std::make_unique<Window>("Text Editor");
    mainwindow->set(std::move(root));

    Application app;
    app.add(mainwindow);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLUE_POWDER);

        app.run();

        EndDrawing();
    }

    CloseWindow();
}