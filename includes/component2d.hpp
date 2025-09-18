#pragma once

#include <raylib.h>

class Component2D
{
public:
    virtual ~Component2D() = default;

    virtual bool intersect(const Component2D &other) const
    {
        return !(position.x + size.x < other.position.x ||
                 other.position.x + other.size.x < position.x ||
                 position.y + size.y < other.position.y ||
                 other.position.y + other.size.y < position.y);
    }

    virtual bool intersect(const Vector2 &other) const
    {
        return (other.x >= position.x && other.x <= position.x + size.x && other.y >= position.y && other.y <= position.y + size.y);
    }

    Vector2 position{};
    Vector2 size{};
};