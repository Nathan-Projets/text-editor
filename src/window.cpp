#include "../includes/window.hpp"

Window::Window(const std::string &title, int width, int height) : _title(title), _width(width), _height(height)
{
    InitWindow(width, height, title.c_str());
}

void Window::update()
{
    std::vector<Event> events;
    Vector2 mouse = GetMousePosition();

    // TODO: come up with a cleaner and more flexible way of managing keys

    static int lastKey = 0;
    static float repeatTimer = 0.0f;
    const float repeatDelay = 0.5f;
    const float repeatRate = 0.05f;

    int key = GetKeyPressed();
    while (key > 0)
    {
        events.push_back({.keyPressed = key, .charPressed = GetCharPressed(), .mouse = mouse});

        if (key == KEY_BACKSPACE)
        {
            lastKey = key;
            repeatTimer = repeatDelay;
        }

        key = GetKeyPressed();
    }

    float dt = GetFrameTime();

    if (IsKeyDown(lastKey))
    {
        repeatTimer -= dt;
        if (repeatTimer <= 0.0f)
        {
            events.push_back({.keyPressed = lastKey, .charPressed = 0, .mouse = mouse});
            repeatTimer = repeatRate; // schedule next repeat
        }
    }
    else
    {
        lastKey = 0; // reset when released
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