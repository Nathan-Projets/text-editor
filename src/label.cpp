#include "../includes/label.hpp"

void Label::render()
{
    if (_dirty)
    {
        int width = MeasureText(_data.c_str(), _fontsize);
        size.x = _padding.x * 2 + width;
        size.y = _padding.y * 2 + _fontsize;
    }

    DrawText(_data.c_str(), _padding.x + position.x, _padding.y + position.y, _fontsize, BLACK);
}

void Label::setFontsize(int fontsize)
{
    _dirty = true;
    _fontsize = fontsize;
}

void Label::setData(const std::string &data)
{
    _dirty = true;
    _data = data;
}

void Label::setData(std::string &&data)
{
    _dirty = true;
    _data = std::move(data);
}

void Label::setPadding(const Vector2 &padding)
{
    _dirty = true;
    _padding = padding;
}