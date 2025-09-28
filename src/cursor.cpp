#include "../includes/cursor.hpp"

void Cursor::update(const Keyboard &keyboard)
{
    _blinkTimer.update();

    if (_blinkTimer.finished())
    {
        _switch = !_switch;
    }
}

void Cursor::render()
{
    Color blinkColor = _switch ? _color : TRANSPARENT;

    DrawRectangle(position.x, position.y, 2, _fontsize, blinkColor);
}

int &Cursor::begin()
{
    return _start;
}

int &Cursor::end()
{
    return _end;
}

void Cursor::move(int offset)
{
    _start += offset;
}

void Cursor::move(CursorDirection offset)
{
    _start += static_cast<int>(offset);
}

void Cursor::moveAt(int position)
{
    _start = position;
}

void Cursor::setTimerConfig(float fireDelay, float repeatDelay, bool repeat)
{
    _blinkTimer.setDelays(fireDelay, repeatDelay, repeat);
}

void Cursor::blinkReset()
{
    _switch = true;
    _blinkTimer.reset();
}