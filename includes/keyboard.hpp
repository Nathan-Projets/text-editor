#pragma once

#include <deque>
#include <vector>
#include <iostream>
#include <unordered_map>

#include <raylib.h>

#include "key.hpp"
#include "event.hpp"

#define MAX_HISTORY_BUFFER 32

class Keyboard
{
public:
    void update();

    Key &get(KeyboardKey keycode);

    bool isPressed(KeyboardKey key) const;
    bool isComboPressed(std::initializer_list<KeyboardKey> keys) const;
    bool wasSequencePressed(std::vector<KeyboardKey> sequence, double maxDelay = 0.25) const;
    
    const std::vector<Event> &getEvents() const { return _events; }

private:
    struct PressRecord
    {
        KeyboardKey key;
        double timestamp; // seconds from GetTime()
    };

    std::unordered_map<KeyboardKey, Key> _keys;
    std::vector<Event> _events;

    // represent the map between keycode and unicode chars, which is filled during update when key press
    std::unordered_map<KeyboardKey, int> _codepoints;

    std::deque<Keyboard::PressRecord> _pressHistory;
};