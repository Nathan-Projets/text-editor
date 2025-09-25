#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include <raylib.h>

#include "container.hpp"
#include "colors.hpp"

enum class Direction
{
    HORIZONTAL,
    VERTICAL
};

class Panel : public Container
{
public:
    explicit Panel();
    explicit Panel(const std::string &title, Direction layout = Direction::HORIZONTAL);

    void update(const Keyboard& keyboard) override;
    void render() override;

    const Color &getBgColor() { return _backgroundColor; }
    void setBgColor(Color color);

    void setSize(int width, int height);
    void setMaxSize(int width, int height);

    const Vector2 &getPadding() { return _padding; };
    void setPadding(const Vector2 &padding);

private:
    std::string _title;
    Direction _layout;
    Color _backgroundColor;

    int _maxWidth, _maxHeight;
    Vector2 _padding;
};