#pragma once

#include <raylib.h>

class Timer
{
public:
    Timer(float fireDelay, float repeatDelay = 0.0f, bool repeat = false)
        : _fireDelay(fireDelay),
          _repeatDelay(repeatDelay > 0.0f ? repeatDelay : fireDelay),
          _repeat(repeat),
          _remaining(fireDelay) {}

    void update();
    bool finished();
    void reset();
    void stop();
    void setDelays(float fireDelay, float repeatDelay = -1.0f, bool repeat = false);
    bool isActive();

private:
    float _fireDelay;   // initial delay before first fire
    float _repeatDelay; // repeat interval
    float _remaining;   // time left until next fire
    bool _repeat;       // should it repeat?
    bool _active = true;
    bool _finished = false;
};