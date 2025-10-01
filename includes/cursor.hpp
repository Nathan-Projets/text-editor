#pragma once

#include <algorithm>
#include <vector>

#include <raylib.h>

#include "timer.hpp"
#include "colors.hpp"
#include "component2d.hpp"

enum class CursorDirection
{
    NONE = 0,
    LEFT = -1,
    RIGHT = 1,
};

class Cursor : public Component2D
{
public:
    Cursor(int fontsize, Color color = WHITE) : _fontsize(fontsize), _position(0), _start(0), _color(color), _switch(false), _isSelecting(false), _blinkTimer(0.4f, 0.4f, true) {}

    void update(const Keyboard &keyboard) override;
    void update(const Keyboard &keyboard, const std::string &data, Vector2 offset = {0.0f, 0.0f});
    void render() override;

    int &at();
    void startSelect();
    void stopSelect();
    bool isSelecting() { return _isSelecting; }

    void move(int offset);
    void move(CursorDirection offset);
    void moveAt(int position);

    void setTimerConfig(float fireDelay, float repeatDelay, bool repeat);
    void blinkReset();

private:
    void drawSelection(Color color) const;
    Vector2 calculatePosition(int index, const std::string &data, Vector2 offset) const;

    int _fontsize, _position, _start;
    Color _color;
    bool _switch, _isSelecting;
    Timer _blinkTimer;

    std::vector<Rectangle> _selectionRects;
};