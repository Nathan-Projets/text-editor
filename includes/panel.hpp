#pragma once

#include <vector>
#include <string>

#include "container.hpp"

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

    void render() override;

private:
    std::string _title;
    Direction _layout;
};