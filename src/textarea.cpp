#include "../includes/textarea.hpp"

// TODO: when selecting and then trying to delete, it throws a string out of range exception

void TextArea::update(const Keyboard &keyboard)
{
    if (_isFocused)
    {
        _cursor.update(keyboard);

        const std::vector<Event> &events = keyboard.getEvents();
        for (size_t eventIt = 0; eventIt < events.size(); eventIt++)
        {
            const Event &event = events[eventIt];

            // handling text input
            if (keyboard.isPressed((KeyboardKey)event.key) && (event.key >= 32) && (event.key <= 125))
            {
                _data.insert(_cursor.at(), 1, event.codepoint);
                _cursor.move(CursorDirection::RIGHT);
                _dirty = true;
            }

            // handling special input
            if (event.key == KEY_BACKSPACE)
            {
                if (keyboard.isPressed((KeyboardKey)event.key) && !_data.empty())
                {
                    if (keyboard.isComboPressed({KEY_LEFT_CONTROL, KEY_BACKSPACE}))
                    {
                        removeWord();
                    }
                    else
                    {
                        _cursor.move(CursorDirection::LEFT);
                        _data.erase(_cursor.at(), 1);
                        _dirty = true;
                    }
                }
            }
            else if (event.key == KEY_ENTER && keyboard.isPressed((KeyboardKey)event.key))
            {
                _data.insert(_cursor.at(), 1, '\n');
                _cursor.move(CursorDirection::RIGHT);
                _dirty = true;
            }
            else if (event.key == KEY_RIGHT && keyboard.isPressed((KeyboardKey)event.key))
            {

                if (keyboard.isComboPressed({KEY_LEFT_CONTROL, KEY_LEFT_SHIFT, KEY_RIGHT}))
                {
                    if (!_cursor.isSelecting())
                    {
                        _cursor.startSelect();
                    }
                    moveByWord(CursorDirection::RIGHT);
                }
                else if (keyboard.isComboPressed({KEY_LEFT_SHIFT, KEY_RIGHT}))
                {
                    if (!_cursor.isSelecting())
                    {
                        _cursor.startSelect();
                    }
                    _cursor.at() = std::min((int)_data.size(), _cursor.at() + 1);
                }
                else if (keyboard.isComboPressed({KEY_LEFT_CONTROL, KEY_RIGHT}))
                {
                    if (_cursor.isSelecting())
                    {
                        _cursor.stopSelect();
                    }
                    moveByWord(CursorDirection::RIGHT);
                }
                else
                {
                    if (_cursor.isSelecting())
                    {
                        _cursor.stopSelect();
                        if (_cursor.at() < _cursor.atSelect())
                        {
                            _cursor.moveAt(_cursor.atSelect());
                        }
                    }
                    else
                    {
                        _cursor.at() = std::min((int)_data.size(), _cursor.at() + 1);
                    }
                }

                _dirty = true;
            }
            else if (event.key == KEY_LEFT && keyboard.isPressed((KeyboardKey)event.key))
            {
                if (keyboard.isComboPressed({KEY_LEFT_CONTROL, KEY_LEFT_SHIFT, KEY_LEFT}))
                {
                    if (!_cursor.isSelecting())
                    {
                        _cursor.startSelect();
                    }
                    moveByWord(CursorDirection::LEFT);
                }
                else if (keyboard.isComboPressed({KEY_LEFT_SHIFT, KEY_LEFT}))
                {
                    if (!_cursor.isSelecting())
                    {
                        _cursor.startSelect();
                    }
                    _cursor.at() = std::max(0, _cursor.at() - 1);
                }
                else if (keyboard.isComboPressed({KEY_LEFT_CONTROL, KEY_LEFT}))
                {
                    if (_cursor.isSelecting())
                    {
                        _cursor.stopSelect();
                    }
                    moveByWord(CursorDirection::LEFT);
                }
                else
                {
                    if (_cursor.isSelecting())
                    {
                        _cursor.stopSelect();
                        if (_cursor.at() > _cursor.atSelect())
                        {
                            _cursor.moveAt(_cursor.atSelect());
                        }
                    }
                    else
                    {
                        _cursor.at() = std::max(0, _cursor.at() - 1);
                    }
                }

                _dirty = true;
            }
        }
    }

    if (_dirty)
    {
        _cursor.update(keyboard, _data, position);
        _dirty = false;
    }
}

void TextArea::render()
{
    _cursor.render();

    DrawText(_data.c_str(), position.x, position.y, _fontsize, BLACK);
}

void TextArea::setIsFocused(bool isFocused)
{
    _isFocused = isFocused;
}

void TextArea::removeWord()
{
    size_t space = _data.substr(0, _cursor.at()).find_last_of(' ');
    if (space != std::string::npos)
    {
        if (space + 1 == _cursor.at())
        {
            space = _data.substr(0, _cursor.at() - 1).find_last_of(' ');
            if (space == std::string::npos)
            {
                _data.erase(0, _cursor.at());
                _cursor.at() = 0;
                return;
            }
        }

        int numberCharsDeleted = _cursor.at() - space - 1;
        _data.erase(space + 1, numberCharsDeleted);
        _cursor.at() -= numberCharsDeleted;
    }
    else
    {
        _data.erase(0, _cursor.at());
        _cursor.at() = 0;
    }

    _dirty = true;
}

void TextArea::moveByWord(CursorDirection direction)
{
    /**
     * case 1: c is alphanum -> go to end word
     * case 2: c is punct
     *         if next character is punct -> go to end of punct word
     *         if next character is alphanumerical -> go to end of next word
     * case 3: c is space
     *         ignore all spaces
     *         if next character is alphanumerical -> go to end of next word
     *         else -> go to end of next punct word
     *
     * else: c is not handled
     */

    int cursor = _cursor.at();
    if (direction == CursorDirection::LEFT)
    {
        cursor--;
        if (cursor < 0)
        {
            _cursor.moveAt(0);
            return;
        }
    }

    int offset = static_cast<int>(direction);
    unsigned char character = static_cast<unsigned char>(_data[cursor]);

    if (std::isalnum(character))
    {
        cursor += offset;
        if (cursor < 0)
        {
            _cursor.moveAt(0);
            return;
        }

        cursor = moveWhile(cursor, offset, [](unsigned char ch)
                           { return std::isalnum(ch); });
    }
    else if (std::ispunct(character))
    {
        cursor += offset;
        if (cursor < 0)
        {
            _cursor.moveAt(0);
            return;
        }

        if (std::isalnum(character))
        {
            cursor = moveWhile(cursor, offset, [](unsigned char ch)
                               { return std::isalnum(ch); });
        }
        else
        {
            cursor = moveWhile(cursor, offset, [](unsigned char ch)
                               { return std::ispunct(ch); });
        }
    }
    else if (std::isspace(character))
    {
        cursor += offset;
        if (cursor < 0)
        {
            _cursor.moveAt(0);
            return;
        }

        cursor = moveWhile(cursor, offset, [](unsigned char ch)
                           { return std::isspace(ch); });

        if (cursor >= 0 || cursor < static_cast<int>(_data.size()))
        {
            // note: I wonder if the cursor should only traverse space characters instead of traversing the next word also
            if (std::isalnum(_data[cursor]))
            {
                cursor = moveWhile(cursor, offset, [](unsigned char ch)
                                   { return std::isalnum(ch); });
            }
            else
            {
                cursor = moveWhile(cursor, offset, [](unsigned char ch)
                                   { return std::ispunct(ch); });
            }
        }
    }
    else
    {
        std::cout << "character is not handled for now: " << character << std::endl;
        return;
    }

    offset = std::min(std::max(0, cursor), (int)_data.size());

    if (direction == CursorDirection::RIGHT)
    {
        _cursor.moveAt(offset);
    }
    else if (direction == CursorDirection::LEFT)
    {
        // left needs one increment to be at the beginning of the word
        _cursor.moveAt(offset ? offset + 1 : 0);
    }
}

int TextArea::moveWhile(int cursor, int offset, auto predicate)
{
    while (predicate(static_cast<unsigned char>(_data[cursor])))
    {
        cursor += offset;
        if (cursor < 0 || cursor >= static_cast<int>(_data.size()))
        {
            break;
        }
    }
    return cursor;
}
