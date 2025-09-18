#include "../includes/container.hpp"

void Container::add(std::unique_ptr<Container> child)
{
    if (child)
    {
        _children.push_back(std::move(child));
    }
}