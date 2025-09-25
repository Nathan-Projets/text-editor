#include "../includes/container.hpp"

void Container::update(const Keyboard& keyboard)
{
    for (std::unique_ptr<Component2D> &child : _children)
    {
        child->update(keyboard);
    }
}

void Container::render()
{
    for (std::unique_ptr<Component2D> &child : _children)
    {
        child->render();
    }
}

void Container::add(std::unique_ptr<Component2D> child)
{
    if (child)
    {
        _children.push_back(std::move(child));
    }
}