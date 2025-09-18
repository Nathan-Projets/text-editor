#include "../includes/window.hpp"

Window::Window(const std::string &title, int width, int height) : _title(title), _width(width), _height(height)
{
    InitWindow(width, height, title.c_str());
}

void Window::update()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        _root->update(mouse);
    }
}

void Window::render()
{
    if (_root)
    {
        _root->render();
    }
}

void Window::set(std::unique_ptr<Container> rootElement)
{
    if (rootElement)
    {
        // destroys previous root element if any
        _root = std::move(rootElement);
    }
}