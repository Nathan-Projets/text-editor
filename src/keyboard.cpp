#include "../includes/keyboard.hpp"

using KeyIterator_t = std::unordered_map<KeyboardKey, Key>::iterator;
using KeyConstIterator_t = std::unordered_map<KeyboardKey, Key>::const_iterator;
using CodepointIterator_t = std::unordered_map<KeyboardKey, int>::iterator;

void Keyboard::update()
{
    _events.clear();

    int keycode = GetKeyPressed();

    while (keycode > 0)
    {
        Key &key = get(static_cast<KeyboardKey>(keycode));
        key.pressed = true;
        key.pressTime = 0.0f;
        key.timer.reset();

        if (_codepoints.find(key.id) == _codepoints.end())
        {
            _codepoints[key.id] = GetCharPressed();
        }

        Event event{EventType::KeyPressed};
        event.key = key.id;
        event.codepoint = _codepoints[key.id];
        event.pressed = true;

        _events.push_back(event);

        _pressHistory.push_back({key.id, GetTime()});

        if (_pressHistory.size() > MAX_HISTORY_BUFFER)
        {
            _pressHistory.pop_front();
        }

        keycode = GetKeyPressed();
    }

    int frameTime = GetFrameTime();

    for (auto &[keycode, key] : _keys)
    {
        if (IsKeyDown(keycode))
        {
            // press
            key.pressTime += frameTime;
            key.timer.update();
            if (key.timer.finished())
            {
                Event event = {.type = EventType::KeyRepeated, .key = key.id};

                CodepointIterator_t it = _codepoints.find(key.id);
                if (it != _codepoints.end())
                {
                    event.codepoint = it->second;
                }

                _events.push_back(event);
            }
        }
        else if (key.pressed)
        {
            // release
            key.pressed = false;
            _events.push_back({.type = EventType::KeyReleased, .key = key.id});
        }
    }
}

Key &Keyboard::get(KeyboardKey keycode)
{
    KeyIterator_t it = _keys.find(keycode);
    if (it != _keys.end())
    {
        return it->second;
    }

    _keys[keycode] = Key{.id = keycode};
    return _keys[keycode];
}

bool Keyboard::isPressed(KeyboardKey key) const
{
    KeyConstIterator_t it = _keys.find(key);
    if (it != _keys.end() && it->second.pressed)
    {
        return true;
    }
    return false;
}

bool Keyboard::isComboPressed(std::initializer_list<KeyboardKey> keys) const
{
    for (const KeyboardKey &key : keys)
    {
        KeyConstIterator_t it = _keys.find(key);
        if (it == _keys.end() || !it->second.pressed)
        {
            return false;
        }
    }
    return true;
}

bool Keyboard::wasSequencePressed(std::vector<KeyboardKey> sequence, double maxDelay) const
{
    if (_pressHistory.size() < sequence.size())
    {
        return false;
    }

    double now = GetTime();
    for (size_t i = 0; i < sequence.size(); i++)
    {
        const Keyboard::PressRecord &record = _pressHistory[_pressHistory.size() - sequence.size() + i];
        if (record.key != sequence[i])
            return false;
        if (now - record.timestamp > maxDelay)
            return false; // too old
    }

    return true;
}