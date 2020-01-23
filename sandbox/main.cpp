#include <cstdlib>

#include <drago2d.hpp>

int main()
{
    if (d2d::init())
        std::exit(0);

    d2d::window_t window(640, 480, "Sandbox");

    while (!d2d::window::should_close(window))
    {
        d2d::window::set_background(window, { 0, 0, 0, 0 });
        
        d2d::draw::fill_rect(0.0, 0.0, 0.1, 0.1, { 1, 0, 0, 1 }, 3.14159 / 4.0);

        d2d::window::poll_events(window);
    }

    d2d::terminate();
}