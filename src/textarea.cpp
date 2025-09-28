#include "../includes/textarea.hpp"

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
            if (event.type != EventType::KeyReleased && (event.key >= 32) && (event.key <= 125))
            {
                _data.insert(_cursor.begin(), 1, event.codepoint);
                _cursor.move(CursorDirection::RIGHT);
                _dirty = true;
            }

            // handling special input
            if (event.key == KEY_BACKSPACE)
            {
                // TODO: add method to keyboard to have proper isPressed, etc
                if (event.type != EventType::KeyReleased && !_data.empty())
                {
                    if (keyboard.isComboPressed({KEY_LEFT_CONTROL, KEY_BACKSPACE}))
                    {
                        removeWord();
                    }
                    else
                    {
                        _cursor.move(CursorDirection::LEFT);
                        _data.erase(_cursor.begin(), 1);
                        _dirty = true;
                    }
                }
            }
            else if (event.key == KEY_ENTER && event.type != EventType::KeyReleased)
            {
                _data.insert(_cursor.begin(), 1, '\n');
                _cursor.move(CursorDirection::RIGHT);
                _dirty = true;
            }
            else if (event.key == KEY_RIGHT && event.type != EventType::KeyReleased)
            {
                if (keyboard.isComboPressed({KEY_LEFT_CONTROL, KEY_RIGHT}))
                {
                    // TODO: move to the right until no alpha char
                    moveByWord(CursorDirection::RIGHT);
                }
                else
                {
                    _cursor.begin() = std::min((int)_data.size(), _cursor.begin() + 1);
                }
                _dirty = true;
            }
            else if (event.key == KEY_LEFT && event.type != EventType::KeyReleased)
            {
                if (keyboard.isComboPressed({KEY_LEFT_CONTROL, KEY_LEFT}))
                {
                    // TODO: move to the left until no alpha char
                    moveByWord(CursorDirection::LEFT);
                }
                else
                {
                    _cursor.begin() = std::max(0, _cursor.begin() - 1);
                }
                _dirty = true;
            }
        }
    }

    if (_dirty)
    {
        // TODO: implement proper line management for the cursor, right now only one line is supported, it's buggy
        int lines = std::count(_data.begin(), _data.end(), '\n');
        int cursorX = MeasureText(_data.substr(0, _cursor.begin()).c_str(), _fontsize);

        _cursor.position.x = position.x + cursorX;
        _cursor.position.y = position.y + lines * _fontsize;
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
    size_t space = _data.substr(0, _cursor.begin()).find_last_of(' ');
    if (space != std::string::npos)
    {
        if (space + 1 == _cursor.begin())
        {
            space = _data.substr(0, _cursor.begin() - 1).find_last_of(' ');
            if (space == std::string::npos)
            {
                _data.erase(0, _cursor.begin());
                _cursor.begin() = 0;
                return;
            }
        }

        int numberCharsDeleted = _cursor.begin() - space - 1;
        _data.erase(space + 1, numberCharsDeleted);
        _cursor.begin() -= numberCharsDeleted;
    }
    else
    {
        _data.erase(0, _cursor.begin());
        _cursor.begin() = 0;
    }

    _dirty = true;
}

void TextArea::moveByWord(CursorDirection direction)
{
    /**
     * [x] case 1: c is alphanum -> go to end word
     * [ ] case 2: c is punct
     *         if next character is punct -> go to end of punct word
     *         if next character is alphanumerical -> go to end of next word
     * [ ] case 3: c is space
     *         if next character is alphanumerical -> go to end of next word
     *         if next character is space -> go to end of next word whathever it is (could be alphanum, or punct, etc)
     *
     * [x] else: c is not handled for now
     *
     *
     * test data: ord1.word2::;?:.word3 word4    word5   .:::?  word6 ().{d } dfs TestMonAmi.PourquoiPas
     * pourquoi pas
     */

    int cursor = _cursor.begin();
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

    std::cout << "should move toward " << (offset > 0 ? "right" : "left") << std::endl;

    if (std::isalnum(character))
    {
        cursor += offset;
        character = static_cast<unsigned char>(_data[cursor]);

        while (std::isalnum(character))
        {
            cursor += offset;
            if (cursor < 0 || cursor >= _data.size())
            {
                break;
            }
            character = static_cast<unsigned char>(_data[cursor]);
        }

        // Set the offset between 0 and the end of data
        int newOffset = std::min(std::max(0, cursor), (int)_data.size());

        if (direction == CursorDirection::RIGHT)
        {
            _cursor.moveAt(newOffset);
        }
        else if (direction == CursorDirection::LEFT)
        {
            // left needs one increment to be at the beginning of the word
            _cursor.moveAt(newOffset ? newOffset + 1 : 0);
        }
    }
    else if (std::ispunct(character))
    {
        std::cout << "character is punct: " << character << std::endl;
        // to implement
    }
    else if (std::isspace(character))
    {
        std::cout << "character is space: " << character << std::endl;
        // to implement
    }
    else
    {
        std::cout << "character is not handled for now: " << character << std::endl;
    }
}