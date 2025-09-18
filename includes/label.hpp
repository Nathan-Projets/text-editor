#pragma once

#include <string>

#include <raylib.h>

#include "component2d.hpp"

class Label : public Component2D
{
public:
    Label() = default;
    Label(const char *data, int fontsize = 20) : _data(data), _fontsize(fontsize) {}
    Label(const std::string &data, int fontsize = 20) : _data(data), _fontsize(fontsize) {}
    Label(std::string &&data, int &&fontsize = 20) noexcept : _data(std::move(data)), _fontsize(std::move(fontsize)) {}

    void render();

    int getFontsize() { return _fontsize; }
    void setFontsize(int fontsize);

    std::string getData() { return _data; }
    void setData(const std::string &data);
    void setData(std::string &&data);

private:
    std::string _data;
    int _fontsize;
};