#pragma once

#include <vector>
#include <memory>

#include "component2d.hpp"

class Container : public Component2D
{
public:
    void update(const Vector2 &mouse) override;
    void render() override;

    void add(std::unique_ptr<Component2D> child);

protected:
    std::vector<std::unique_ptr<Component2D>> _children;
};