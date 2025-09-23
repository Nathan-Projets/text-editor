#include "../includes/window.hpp"

Window::Window(const std::string &title, int width, int height) : _title(title), _width(width), _height(height), _keyPressTimer(0.5f, 0.05f, true)
{
    InitWindow(width, height, title.c_str());
}

void Window::update()
{
    Vector2 mouse = GetMousePosition();

    std::vector<Event> events;

    // TODO: come up with a cleaner and more flexible way of managing keys, support the repeat timer for all keys, not just space also

    static int lastKey = 0;
    static Timer repeatTimer(0.5f, 0.05f, true);

    int key = GetKeyPressed();
    while (key > 0)
    {
        events.push_back({.keyPressed = key, .charPressed = GetCharPressed(), .mouse = mouse});

        if (key == KEY_BACKSPACE)
        {
            lastKey = key;
            repeatTimer.reset();
        }

        key = GetKeyPressed();
    }

    float dt = GetFrameTime();

    if (IsKeyDown(lastKey))
    {
        repeatTimer.update();
        if (repeatTimer.finished())
        {
            events.push_back({.keyPressed = lastKey, .charPressed = 0, .mouse = mouse});
        }
    }
    else
    {
        lastKey = 0; // reset when released
        repeatTimer.stop();
    }

    _root->update(events);
}

void Window::render()
{
    BeginDrawing();
    ClearBackground(BLUE_POWDER);

    if (_root)
    {
        _root->render();
    }

    EndDrawing();
}

void Window::set(std::unique_ptr<Container> rootElement)
{
    if (rootElement)
    {
        // destroys previous root element if any
        _root = std::move(rootElement);
    }
}