#include "../includes/textarea.hpp"

void TextArea::update(const std::vector<Event> &events)
{
    if (_isFocused)
    {
        for (const Event &event : events)
        {
            if (event.keyPressed == KEY_BACKSPACE && !_data.empty())
            {
                // TODO: make the code more readable, and extandable (like range selection in the future, etc)
                if (IsKeyDown(KEY_LEFT_CONTROL))
                {
                    size_t space = _data.substr(0, _cursor).find_last_of(' ');
                    if (space != std::string::npos)
                    {
                        if (space + 1 == _cursor)
                        {
                            space = _data.substr(0, _cursor - 1).find_last_of(' ');
                            if (space == std::string::npos)
                            {
                                _data.erase(0, _cursor);
                                _cursor = 0;
                                continue;
                            }
                        }

                        int numberCharsDeleted = _cursor - space - 1;
                        _data.erase(space + 1, numberCharsDeleted);
                        _cursor -= numberCharsDeleted;
                    }
                    else
                    {
                        _data.erase(0, _cursor);
                        _cursor = 0;
                    }
                }
                else
                {
                    _data.erase(--_cursor, 1);
                }
            }
            else if (event.keyPressed == KEY_ENTER)
            {
                _data.insert(_cursor, 1, '\n');
                _cursor++;
            }
            else if (event.keyPressed == KEY_RIGHT)
            {
                _cursor = std::min((int)_data.size(), _cursor + 1);
            }
            else if (event.keyPressed == KEY_LEFT)
            {
                _cursor = std::max(0, _cursor - 1);
            }

            if ((event.keyPressed >= 32) && (event.keyPressed <= 125))
            {
                _data.insert(_cursor, 1, event.charPressed);
                _cursor++;
            }
        }
    }
}

void TextArea::render()
{
    // TODO: implement generic way to create timer (at this commit there are already two places where this kind of timer is and I'm not a fan of making static variable like this)
    float dt = GetFrameTime();

    static float blinkDelay = 0.4f;
    static float blinkTimer = 0.0f;
    static Color blinkColor = TRANSPARENT;
    static bool blinkColorChange = false;

    blinkTimer -= dt;
    if (blinkTimer <= 0.0f)
    {
        blinkColor = blinkColorChange ? TRANSPARENT : WHITE;
        blinkColorChange = !blinkColorChange;
        blinkTimer = blinkDelay;
    }

    // TODO: implement the dirty system here to avoid remeasuring the text even when nothing changes, probably better to create a seperate class for the cursor
    int cursorX = MeasureText(_data.substr(0, _cursor).c_str(), _fontsize);

    // TODO: implement proper line management for the cursor, right now only one line is supported, it's buggy
    int lines = std::count(_data.begin(), _data.end(), '\n');

    // draw cursor
    DrawRectangle(position.x + cursorX, position.y + lines * _fontsize, 2, _fontsize, blinkColor);

    // draw textarea content
    DrawText(_data.c_str(), position.x, position.y, _fontsize, BLACK);
}

void TextArea::setIsFocused(bool isFocused)
{
    _isFocused = isFocused;
}