#pragma once

#include <raylib.h>

struct Event
{
    int keyPressed = -1;
    int charPressed = -1;
    Vector2 mouse = {-1, -1};
};
