#pragma once

#include <vector>
#include <string>
#include <memory>

#include "container.hpp"
#include "colors.hpp"
#include "event.hpp"

class Window
{
public:
    Window(const std::string &title, int width = 800, int height = 450);

    void update();
    void render();
    void set(std::unique_ptr<Container> rootElement);

private:
    std::unique_ptr<Container> _root;

    std::string _title;
    int _width, _height;
};