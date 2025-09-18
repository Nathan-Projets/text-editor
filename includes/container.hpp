#pragma once

#include <vector>
#include <memory>

class Container
{
public:
    void add(std::unique_ptr<Container> child);
    virtual void render() = 0;

private:
    std::vector<std::unique_ptr<Container>> _children;
};