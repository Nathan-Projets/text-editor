#pragma once

#include <vector>

#include <raylib.h>

#include "timer.hpp"
#include "colors.hpp"
#include "component2d.hpp"

// TODO: add usual fast movement shortcut like ctrl+right, ctrl+left, etc.
// TODO: add range selection logic

enum class CursorDirection
{
    NONE = 0,
    LEFT = -1,
    RIGHT = 1,
};

class Cursor : public Component2D
{
public:
    Cursor(int fontsize, Color color = WHITE) : _fontsize(fontsize), _start(0), _end(0), _color(color), _switch(false), _blinkTimer(0.4f, 0.4f, true) {}

    void update(const Keyboard &keyboard) override;
    void render() override;

    int &begin();
    int &end();

    void move(int offset);
    void move(CursorDirection offset);
    void moveAt(int position);

    void setTimerConfig(float fireDelay, float repeatDelay, bool repeat);

private:
    int _fontsize, _start, _end;
    Color _color;
    bool _switch;
    Timer _blinkTimer;
};