#include "../includes/button.hpp"

void Button::click()
{
    if (_handlerClick)
    {
        _handlerClick();
    }
}

void Button::render()
{
    DrawText(_data.c_str(), position.x, position.y, _fontsize, BLACK);
}

void Button::setFontsize(int fontsize)
{
    _fontsize = fontsize;
}

void Button::setData(const std::string &data)
{
    _data = data;
}

void Button::setData(std::string &&data)
{
    _data = std::move(data);
}

void Button::setHandlerClick(std::function<void()> handler)
{
    _handlerClick = std::move(handler);
}