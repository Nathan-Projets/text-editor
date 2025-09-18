#pragma once

#include <string>

#include <raylib.h>

#include "component2d.hpp"

class Label : public Component2D
{
public:
    Label() = default;
    Label(const char *data, int fontsize = 20) : _data(data), _fontsize(fontsize), _padding(0, 0), _dirty(true) {}
    Label(const std::string &data, int fontsize = 20) : _data(data), _fontsize(fontsize), _padding(0, 0), _dirty(true) {}
    Label(std::string &&data, int &&fontsize = 20) noexcept : _data(std::move(data)), _fontsize(std::move(fontsize)), _padding(0, 0), _dirty(true) {}

    void render();

    int getFontsize() { return _fontsize; }
    void setFontsize(int fontsize);

    const Vector2 &getPadding() { return _padding; };
    void setPadding(const Vector2 &padding);

    std::string getData() { return _data; }
    void setData(const std::string &data);
    void setData(std::string &&data);

private:
    std::string _data;
    int _fontsize;
    Vector2 _padding;
    bool _dirty;
};