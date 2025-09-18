#pragma once

#include <vector>
#include <memory>

#include <raylib.h>

#include "window.hpp"

class Application
{
public:
    void run();
    void add(std::unique_ptr<Window>& window);

private:
    std::vector<std::unique_ptr<Window>> _windows;
};