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
    if (_dirty)
    {
        int width = MeasureText(_data.c_str(), _fontsize);
        size.x = _padding.x * 2 + width;
        size.y = _padding.y * 2 + _fontsize;
    }

    DrawRectangle(position.x, position.y, size.x, size.y, GREEN);
    DrawText(_data.c_str(), _padding.x + position.x, _padding.y + position.y, _fontsize, BLACK);
}

void Button::setFontsize(int fontsize)
{
    _dirty = true;
    _fontsize = fontsize;
}

void Button::setData(const std::string &data)
{
    _dirty = true;
    _data = data;
}

void Button::setData(std::string &&data)
{
    _dirty = true;
    _data = std::move(data);
}

void Button::setPadding(const Vector2 &padding)
{
    _dirty = true;
    _padding = padding;
}

void Button::setHandlerClick(std::function<void()> handler)
{
    _handlerClick = std::move(handler);
}