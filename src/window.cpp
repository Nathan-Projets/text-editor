#include "../includes/window.hpp"

Window::Window(const std::string &title, int width, int height) : _title(title), _width(width), _height(height), _keyPressTimer(0.5f, 0.05f, true), _keyboard()
{
    InitWindow(width, height, title.c_str());
}

void Window::update()
{
    _keyboard.update();

    _root->update(_keyboard);
}

void Window::render()
{
    BeginDrawing();
    ClearBackground(BLUE_POWDER);

    if (_root)
    {
        _root->render();
    }

    EndDrawing();
}

void Window::set(std::unique_ptr<Container> rootElement)
{
    if (rootElement)
    {
        // destroys previous root element if any
        _root = std::move(rootElement);
    }
}