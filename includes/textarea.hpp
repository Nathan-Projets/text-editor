#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <raylib.h>

#include "colors.hpp"
#include "component2d.hpp"

class TextArea : public Component2D
{
public:
    TextArea(int fontsize = 20) : _data(), _fontsize(fontsize), _isFocused(false), _cursor(0) {}
    TextArea(const std::string &data, int fontsize = 20) : _data(data), _fontsize(fontsize), _isFocused(false), _cursor(0) {}

    void update(const std::vector<Event>& events) override;
    void render() override;

    bool isFocused() { return _isFocused; }
    void setIsFocused(bool isFocused);

private:
    std::string _data;
    int _fontsize;
    bool _isFocused;

    int _cursor;
};