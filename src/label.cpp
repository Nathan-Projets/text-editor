#include "../includes/label.hpp"

void Label::render()
{
    DrawText(_data.c_str(), position.x, position.y, _fontsize, BLACK);
}

void Label::setFontsize(int fontsize)
{
    _fontsize = fontsize;
}

void Label::setData(const std::string &data)
{
    _data = data;
}

void Label::setData(std::string &&data)
{
    _data = std::move(data);
}