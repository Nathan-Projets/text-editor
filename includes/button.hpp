#pragma once

#include <functional>
#include <string>

#include <raylib.h>

#include "component2d.hpp"

class Button : public Component2D
{
public:
    Button() = default;
    Button(const char *data, int fontsize = 20) : _data(data), _fontsize(fontsize) {}
    Button(const std::string &data, int fontsize = 20) : _data(data), _fontsize(fontsize) {}
    Button(std::string &&data, int &&fontsize = 20) noexcept : _data(std::move(data)), _fontsize(std::move(fontsize)) {}

    void click();
    void render();

    int getFontsize() { return _fontsize; }
    void setFontsize(int fontsize);

    std::string getData() { return _data; }
    void setData(const std::string &data);
    void setData(std::string &&data);

    void setHandlerClick(std::function<void()> handler);

private:
    std::string _data;
    int _fontsize;

    std::function<void()> _handlerClick;
};