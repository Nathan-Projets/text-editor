#pragma once

#include <raylib.h>

#include "timer.hpp"

struct Key
{
    KeyboardKey id = KEY_NULL;
    bool pressed = false;
    float pressTime = 0.0f;
    Timer timer = {0.5f, 0.05f, true};
};