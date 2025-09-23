#include "../includes/timer.hpp"

void Timer::update()
{
    if (!_active)
    {
        return;
    }

    _remaining -= GetFrameTime();
    if (_remaining <= 0.0f)
    {
        _finished = true;

        if (_repeat)
        {
            _remaining = _repeatDelay; // schedule next repeat
        }
        else
        {
            _active = false; // stop
        }
    }
}

bool Timer::finished()
{
    if (_finished)
    {
        _finished = false; // reset
        return true;
    }
    return false;
}

void Timer::reset()
{
    _remaining = _fireDelay;
    _active = true;
    _finished = false;
}

void Timer::stop()
{
    _active = false;
    _finished = false;
}

void Timer::setDelays(float fireDelay, float repeatDelay, bool repeat)
{
    _fireDelay = fireDelay;
    _repeatDelay = (repeatDelay > 0 ? repeatDelay : fireDelay);
    _repeat = repeat;
    reset();
}

bool Timer::isActive()
{
    return _active;
}