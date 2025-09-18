#include "../includes/application.hpp"

void Application::run()
{
    for (std::unique_ptr<Window> &window : _windows)
    {
        if (window)
        {
            window->render();
        }
    }
}

void Application::add(std::unique_ptr<Window> window)
{
    if (window)
    {
        _windows.push_back(std::move(window));
    }
}