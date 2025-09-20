#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <raylib.h>

#include "component2d.hpp"

class TextArea : public Component2D
{
public:
    TextArea(int fontsize = 20) : _data(), _fontsize(fontsize), _isFocused(false) {}
    TextArea(const std::string &data, int fontsize = 20) : _data(data), _fontsize(fontsize), _isFocused(false) {}

    void update(const std::vector<Event>& events) override;
    void render() override;

    bool isFocused() { return _isFocused; }
    void setIsFocused(bool isFocused);

private:
    std::string _data;
    int _fontsize;
    bool _isFocused;
};