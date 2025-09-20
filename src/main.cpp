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

    std::unique_ptr<Panel> left = std::make_unique<Panel>("Left panel", Direction::VERTICAL);
    left->setBgColor(BLUE_POWDER_DARKER);
    left->setSize(200, 450);
    std::unique_ptr<Panel> right = std::make_unique<Panel>("Right panel", Direction::VERTICAL);
    right->setBgColor(BLUE_POWDER);
    right->setSize(600, 450);

    std::unique_ptr<Panel> root = std::make_unique<Panel>("Main panel", Direction::HORIZONTAL);
    root->add(std::move(left));
    root->add(std::move(right));

    std::unique_ptr<Window> mainwindow = std::make_unique<Window>("Text Editor");
    mainwindow->set(std::move(root));

    Application app;
    app.add(mainwindow);

    while (!WindowShouldClose())
    {
        app.run();
    }

    CloseWindow();
}