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

    void update(const Vector2 &mouse) override;
    void render() override;

    void setBgColor(Color color);
    void setSize(int width, int height);
    void setMaxSize(int width, int height);

private:
    std::string _title;
    Direction _layout;
    Color _backgroundColor;

    int _maxWidth, _maxHeight;
};