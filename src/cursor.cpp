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

    // TODO: multilines is not supported well, fix it
    if (isSelecting())
    {
        int selectionStart = std::min(_start, at());
        int selectionEnd = std::max(_start, at());

        int startLine = static_cast<int>(std::count(data.begin(), data.begin() + selectionStart, '\n'));
        int endLine = static_cast<int>(std::count(data.begin(), data.begin() + selectionEnd, '\n'));

        // note: 2 is by default from raylib variable textLineSpacing, if needs come to handle it properly I need to call SetTextLineSpacing to set a custom spacing
        int lineSpacing = _fontsize + 2;

        for (int line = startLine; line <= endLine; ++line)
        {
            size_t lineStart = (line == 0) ? 0 : data.rfind('\n', selectionStart) + 1;
            if (lineStart == std::string::npos)
            {
                lineStart = 0;
            }
            size_t lineEnd = data.find('\n', lineStart);
            if (lineEnd == std::string::npos)
            {
                lineEnd = data.size();
            }

            std::string lineText = data.substr(lineStart, lineEnd - lineStart);

            int y = offset.y + line * lineSpacing;

            int startIndex = (line == startLine) ? selectionStart - lineStart : 0;
            int endIndex = (line == endLine) ? selectionEnd - lineStart : static_cast<int>(lineText.size());

            int xStart = offset.x + MeasureText(lineText.substr(0, startIndex).c_str(), _fontsize);
            int xEnd = offset.x + MeasureText(lineText.substr(0, endIndex).c_str(), _fontsize);

            _selectionRects.push_back({static_cast<float>(xStart), static_cast<float>(y),
                                       static_cast<float>(xEnd - xStart), static_cast<float>(lineSpacing)});
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