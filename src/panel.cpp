#include "../includes/panel.hpp"

Panel::Panel() : _title(), _layout(Direction::HORIZONTAL)
{
}

Panel::Panel(const std::string &title, Direction layout) : _title(title), _layout(layout)
{
}

void Panel::render()
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

        child->render();
    }
}