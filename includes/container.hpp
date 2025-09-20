#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "event.hpp"
#include "component2d.hpp"

class Container : public Component2D
{
public:
    void update(const std::vector<Event>& events) override;
    void render() override;

    void add(std::unique_ptr<Component2D> child);

protected:
    std::vector<std::unique_ptr<Component2D>> _children;
};