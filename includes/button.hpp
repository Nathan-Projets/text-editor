#pragma once

#include <functional>
#include <string>

#include <raylib.h>

#include "component2d.hpp"
#include "colors.hpp"

class Button : public Component2D
{
public:
    Button() = default;
    Button(const char *data, int fontsize = 20) : _data(data), _fontsize(fontsize), _padding(0, 0), _dirty(true) {}
    Button(const std::string &data, int fontsize = 20) : _data(data), _fontsize(fontsize), _padding(0, 0), _dirty(true) {}
    Button(std::string &&data, int &&fontsize = 20) noexcept : _data(std::move(data)), _fontsize(std::move(fontsize)), _padding(0, 0), _dirty(true) {}

    void click();
    void update(const Vector2 &mouse) override;
    void render() override;

    int getFontsize() { return _fontsize; }
    void setFontsize(int fontsize);

    const std::string &getData() { return _data; }
    void setData(const std::string &data);
    void setData(std::string &&data);

    const Vector2 &getPadding() { return _padding; };
    void setPadding(const Vector2 &padding);

    void setHandlerClick(std::function<void()> handler);

private:
    std::string _data;
    int _fontsize;
    Vector2 _padding;
    bool _dirty;

    std::function<void()> _handlerClick;
};