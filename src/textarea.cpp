#include "../includes/textarea.hpp"

void TextArea::update(const std::vector<Event> &events)
{
    if (_isFocused)
    {
        _cursor.update(events);

        for (const Event &event : events)
        {
            if (event.keyPressed == KEY_BACKSPACE && !_data.empty())
            {
                // TODO: make the code more readable, and extandable (like range selection in the future, etc)
                if (IsKeyDown(KEY_LEFT_CONTROL))
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
                                _dirty = true;
                                continue;
                            }
                        }

                        int numberCharsDeleted = _cursor.begin() - space - 1;
                        _data.erase(space + 1, numberCharsDeleted);
                        _cursor.begin() -= numberCharsDeleted;
                        _dirty = true;
                    }
                    else
                    {
                        _data.erase(0, _cursor.begin());
                        _cursor.begin() = 0;
                        _dirty = true;
                    }
                }
                else
                {
                    _data.erase(--_cursor.begin(), 1);
                    _dirty = true;
                }
            }
            else if (event.keyPressed == KEY_ENTER)
            {
                _data.insert(_cursor.begin(), 1, '\n');
                _cursor.begin()++;
                _dirty = true;
            }
            else if (event.keyPressed == KEY_RIGHT)
            {
                _cursor.begin() = std::min((int)_data.size(), _cursor.begin() + 1);
                _dirty = true;
            }
            else if (event.keyPressed == KEY_LEFT)
            {
                _cursor.begin() = std::max(0, _cursor.begin() - 1);
                _dirty = true;
            }

            if ((event.keyPressed >= 32) && (event.keyPressed <= 125))
            {
                _data.insert(_cursor.begin(), 1, event.charPressed);
                _cursor.begin()++;
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