#include "../includes/cursor.hpp"

void Cursor::update(const Keyboard &keyboard)
{
    _blinkTimer.update();

    if (_blinkTimer.finished())
    {
        _switch = !_switch;
    }
}

void Cursor::update(const Keyboard &keyboard, const std::string &data, Vector2 offset)
{
    position = calculatePosition(at(), data, offset);

    _selectionRects.clear();

    if (isSelecting())
    {
        int selectionStart = std::min(_start, at());
        int selectionEnd = std::max(_start, at());

        int startLine = static_cast<int>(std::count(data.begin(), data.begin() + selectionStart, '\n'));
        int endLine = static_cast<int>(std::count(data.begin(), data.begin() + selectionEnd, '\n'));

        // note: 2 is by default from raylib variable textLineSpacing, if needs come to handle it properly I need to call SetTextLineSpacing to set a custom spacing
        float lineSpacing = _fontsize + 2;

        size_t searchPos = 0;
        for (int line = 0; line <= endLine; ++line)
        {
            size_t lineStart = searchPos;
            size_t lineEnd = data.find('\n', lineStart);
            if (lineEnd == std::string::npos)
            {
                lineEnd = data.size();
            }

            if (line >= startLine)
            {
                float y = offset.y + line * lineSpacing;

                // clamp selection
                size_t selStart = (line == startLine) ? selectionStart : lineStart;
                size_t selEnd = (line == endLine) ? selectionEnd : lineEnd;

                selStart = std::max(selStart, lineStart);
                selEnd = std::min(selEnd, lineEnd);

                if (selStart < selEnd)
                {
                    std::string lineText = data.substr(lineStart, lineEnd - lineStart);

                    int startIndex = static_cast<int>(selStart - lineStart);
                    int endIndex = static_cast<int>(selEnd - lineStart);

                    float xStart = offset.x + MeasureText(lineText.substr(0, startIndex).c_str(), _fontsize);
                    float xEnd = offset.x + MeasureText(lineText.substr(0, endIndex).c_str(), _fontsize);

                    _selectionRects.push_back({xStart, y, xEnd - xStart, lineSpacing});
                }
            }

            searchPos = lineEnd + 1;
        }
    }

    blinkReset();
}

void Cursor::render()
{
    Color blinkColor = _switch ? _color : TRANSPARENT;

    // draw range selection
    drawSelection(_color);

    // draw cursor
    DrawRectangle(position.x, position.y, 2, _fontsize, blinkColor);
}

int &Cursor::at()
{
    return _position;
}

int &Cursor::atSelect()
{
    return _start;
}

void Cursor::startSelect()
{
    _isSelecting = true;
    _start = at();
}

void Cursor::stopSelect()
{
    _isSelecting = false;
}

void Cursor::move(int offset)
{
    _position += offset;
}

void Cursor::move(CursorDirection offset)
{
    _position += static_cast<int>(offset);
}

void Cursor::moveAt(int position)
{
    _position = position;
}

void Cursor::setTimerConfig(float fireDelay, float repeatDelay, bool repeat)
{
    _blinkTimer.setDelays(fireDelay, repeatDelay, repeat);
}

void Cursor::blinkReset()
{
    _switch = true;
    _blinkTimer.reset();
}

void Cursor::drawSelection(Color color) const
{
    for (const Rectangle &rectangle : _selectionRects)
    {
        DrawRectangleRec(rectangle, color);
    }
}

Vector2 Cursor::calculatePosition(int index, const std::string &data, Vector2 offset) const
{
    int lines = static_cast<int>(std::count(data.begin(), data.begin() + index, '\n'));
    int totalHeight = lines * (_fontsize + 2);

    int cursor = index;
    if (cursor > 0)
    {
        cursor--;
    }

    size_t lineStart = data.rfind('\n', cursor);
    if (lineStart == std::string::npos)
    {
        lineStart = 0;
    }
    else
    {
        lineStart += 1;
    }

    std::string currentLine = data.substr(lineStart, index - lineStart);

    int lineWidth = MeasureText(currentLine.c_str(), _fontsize);
    int lineHeight = lineStart ? totalHeight : 0;

    Vector2 pos;
    pos.x = offset.x + lineWidth;
    pos.y = offset.y + lineHeight;

    if (index == 0 || index == static_cast<int>(lineStart))
    {
        pos.x -= 2;
    }

    return pos;
}