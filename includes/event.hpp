#pragma once

#include <raylib.h>

enum class EventType
{
    EventUnknown,
    KeyPressed,
    KeyReleased,
    KeyRepeated,
    CharInput,
    MouseMoved,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseWheel,
};

struct Event
{
    EventType type = EventType::EventUnknown;

    // Keyboard
    int key = 0;       // raylib keycode
    int codepoint = 0; // Unicode codepoint from GetCharPressed()

    // Mouse
    Vector2 mouse = {0.0f, 0.0f};
    int mouseButton = -1;
    float wheelDelta = 0.0f;

    // Flags
    bool pressed = false;
    bool released = false;
    bool repeated = false;
};