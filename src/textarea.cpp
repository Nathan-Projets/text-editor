#include "../includes/textarea.hpp"

void TextArea::update(const Keyboard &keyboard)
{
    if (_isFocused)
    {
        _cursor.update(keyboard);

        const std::vector<Event> &events = keyboard.getEvents();
        for (size_t eventIt = 0; eventIt < events.size(); eventIt++)
        {
            const Event &event = events[eventIt];

            // handling text input
            if (event.type != EventType::KeyReleased && (event.key >= 32) && (event.key <= 125))
            {
                _data.insert(_cursor.begin(), 1, event.codepoint);
                _cursor.right();
                _dirty = true;
            }

            // handling special input
            if (event.key == KEY_BACKSPACE)
            {
                // TODO: add method to keyboard to have proper isPressed, etc
                if (event.type != EventType::KeyReleased && !_data.empty())
                {
                    if (keyboard.isComboPressed({KEY_LEFT_CONTROL, KEY_BACKSPACE}))
                    {
                        removeWord();
                    }
                    else
                    {
                        _data.erase(_cursor.begin(), 1);
                        _cursor.left();
                        _dirty = true;
                    }
                }
            }
            else if (event.key == KEY_ENTER && event.type != EventType::KeyReleased)
            {
                _data.insert(_cursor.begin(), 1, '\n');
                _cursor.right();
                _dirty = true;
            }
            else if (event.key == KEY_RIGHT && event.type != EventType::KeyReleased)
            {
                if (keyboard.isComboPressed({KEY_LEFT_CONTROL, KEY_RIGHT}))
                {
                    // TODO: move to the right until no alpha char
                }
                else
                {
                    _cursor.begin() = std::min((int)_data.size(), _cursor.begin() + 1);
                }
                _dirty = true;
            }
            else if (event.key == KEY_LEFT && event.type != EventType::KeyReleased)
            {
                if (keyboard.isComboPressed({KEY_LEFT_CONTROL, KEY_LEFT}))
                {
                    // TODO: move to the left until no alpha char
                }
                else
                {
                    _cursor.begin() = std::max(0, _cursor.begin() - 1);
                }
                _dirty = true;
            }
        }
    }

    if (_dirty)
    {
        // TODO: implement proper line management for the cursor, right now only one line is supported, it's buggy
        int lines = std::count(_data.begin(), _data.end(), '\n');
        int cursorX = MeasureText(_data.substr(0, _cursor.begin()).c_str(), _fontsize);

        _cursor.position.x = position.x + cursorX;
        _cursor.position.y = position.y + lines * _fontsize;
    }
}

void TextArea::render()
{
    _cursor.render();

    DrawText(_data.c_str(), position.x, position.y, _fontsize, BLACK);
}

void TextArea::setIsFocused(bool isFocused)
{
    _isFocused = isFocused;
}

void TextArea::removeWord()
{
    size_t space = _data.substr(0, _cursor.begin()).find_last_of(' ');
    if (space != std::string::npos)
    {
        if (space + 1 == _cursor.begin())
        {
            space = _data.substr(0, _cursor.begin() - 1).find_last_of(' ');
            if (space == std::string::npos)
            {
                _data.erase(0, _cursor.begin());
                _cursor.begin() = 0;
                return;
            }
        }

        int numberCharsDeleted = _cursor.begin() - space - 1;
        _data.erase(space + 1, numberCharsDeleted);
        _cursor.begin() -= numberCharsDeleted;
    }
    else
    {
        _data.erase(0, _cursor.begin());
        _cursor.begin() = 0;
    }

    _dirty = true;
}