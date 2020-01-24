#include <cstdlib>

#include <drago2d.hpp>

int main()
{
    if (d2d::init())
        std::exit(0);

    d2d::window_t window(640, 480, "Sandbox");

    double x, y, a;

    while (!d2d::window::should_close(window))
    {
        d2d::window::set_background({ 0, 0, 0, 0 });
        
        d2d::window::get_cursor_pos(window, x, y);
        d2d::draw::fill_rect(x, y, 50, 50, { 1, 0, 0, 1 }, a);

        a += 0.01;
        d2d::window::poll_events(window);
    }

    d2d::terminate();
}