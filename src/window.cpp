#include "../includes/window.hpp"

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