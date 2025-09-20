#include "../includes/textarea.hpp"

void TextArea::update(const std::vector<Event> &events)
{
    if (_isFocused)
    {
        for (const Event &event : events)
        {
            if (event.keyPressed == KEY_BACKSPACE && !_data.empty())
            {
                _data.pop_back();
            }
            else if (event.keyPressed == KEY_ENTER)
            {
                _data += '\n';
            }

            if ((event.keyPressed >= 32) && (event.keyPressed <= 125))
            {
                _data += event.charPressed;
            }
        }
    }
}

void TextArea::render()
{
    DrawText(_data.c_str(), position.x, position.y, _fontsize, BLACK);
}

void TextArea::setIsFocused(bool isFocused)
{
    _isFocused = isFocused;
}