#pragma once

#include <vector>
#include <memory>

#include "container.hpp"

class Window
{
public:
    void render();
    void set(std::unique_ptr<Container> rootElement);

private:
    std::unique_ptr<Container> _root;
};