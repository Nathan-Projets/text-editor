#include "../includes/panel.hpp"

Panel::Panel() : _title(), _layout(Direction::HORIZONTAL), _backgroundColor(TRANSPARENT), _maxWidth(INT_MAX), _maxHeight(INT_MAX), _padding(0, 0)
{
}

Panel::Panel(const std::string &title, Direction layout) : _title(title), _layout(layout), _backgroundColor(TRANSPARENT), _maxWidth(INT_MAX), _maxHeight(INT_MAX), _padding(0, 0)
{
}

void Panel::update(const Keyboard& keyboard)
{
    int totalShift = 0;
    for (std::unique_ptr<Component2D> &child : _children)
    {
        child->position.x = _padding.x + position.x;
        child->position.y = _padding.y + position.y;

        if (_layout == Direction::HORIZONTAL)
        {
            child->position.x += totalShift;
            totalShift += child->size.x;
        }
        else if (_layout == Direction::VERTICAL)
        {
            child->position.y += totalShift;
            totalShift += child->size.y;
        }

        child->update(keyboard);
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

void Panel::setPadding(const Vector2 &padding)
{
    _padding = padding;
}