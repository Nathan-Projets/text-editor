#include "../includes/panel.hpp"

Panel::Panel() : _title(), _layout(Direction::HORIZONTAL), _backgroundColor(TRANSPARENT), _maxWidth(INT_MAX), _maxHeight(INT_MAX)
{
}

Panel::Panel(const std::string &title, Direction layout) : _title(title), _layout(layout), _backgroundColor(TRANSPARENT), _maxWidth(INT_MAX), _maxHeight(INT_MAX)
{
}

void Panel::update(const Vector2 &mouse)
{
    int totalShift = 0;
    for (std::unique_ptr<Component2D> &child : _children)
    {
        if (_layout == Direction::HORIZONTAL)
        {
            child->position.x = position.x + totalShift;
            totalShift += child->size.x;
        }
        else if (_layout == Direction::VERTICAL)
        {
            child->position.y = position.y + totalShift;
            totalShift += child->size.y;
        }

        child->update(mouse);
    }
}

void Panel::render()
{
    if (!sameColor(_backgroundColor, TRANSPARENT) && size.x > 0 && size.y > 0)
    {
        int sizeX = std::min(static_cast<int>(size.x), _maxWidth);
        int sizeY = std::min(static_cast<int>(size.y), _maxHeight);
        DrawRectangle(position.x, position.y, sizeX, sizeY, _backgroundColor);
    }

    for (std::unique_ptr<Component2D> &child : _children)
    {
        child->render();
    }
}

void Panel::setBgColor(Color color)
{
    _backgroundColor = color;
}

void Panel::setSize(int width, int height)
{
    size.x = width;
    size.y = height;
}

void Panel::setMaxSize(int width, int height)
{
    _maxWidth = width;
    _maxHeight = height;
}