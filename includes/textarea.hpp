#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cctype>

#include <raylib.h>

#include "cursor.hpp"
#include "colors.hpp"
#include "component2d.hpp"

class TextArea : public Component2D
{
public:
    TextArea(int fontsize = 20, Color color = WHITE) : _data(), _fontsize(fontsize), _isFocused(false), _dirty(true), _cursor(fontsize, color) {}
    TextArea(const std::string &data, int fontsize = 20, Color color = WHITE) : _data(data), _fontsize(fontsize), _isFocused(false), _dirty(true), _cursor(fontsize, color) {}

    void update(const Keyboard& keyboard) override;
    void render() override;

    bool isFocused() { return _isFocused; }
    void setIsFocused(bool isFocused);

private:

    void removeWord();
    void moveByWord(CursorDirection direction);

    std::string _data;
    int _fontsize;
    bool _isFocused, _dirty;

    Cursor _cursor;
};