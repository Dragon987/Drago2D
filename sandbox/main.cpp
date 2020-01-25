#include <cstdlib>

#include <drago2d.hpp>

double a = 0.0f;

int main()
{
    if (d2d::init())
        std::exit(0);

    d2d::window_t window(640, 480, "Sandbox");

    double x, y;

    d2d::window::set_onclick_function(window, [](d2d::window_t&, int, int, int) {
        a = 0.0f;
    });

    while (!d2d::window::should_close(window))
    {
        d2d::window::set_background({ a / 2, a / 4, a / 8, a / 16 });
        
        d2d::window::get_cursor_pos(window, x, y);
        d2d::draw::fill_rect(x, y, 50, 50, { 1, 0, 0, 1 }, a);

        d2d::draw::draw_rect(300, 300, 100, 20, { 0, 0, 1, 1 }, 0);
        d2d::draw::line(0, 0, 640, 480, { 0, 1, 0, 1});

        d2d::draw::fill_circle(100, 400, 50, { 1, 0, 1, 1 });
        d2d::draw::draw_circle(400, 100, 50, { 0, 1, 1, 1 });

        a += 0.01;
        d2d::window::poll_events(window);
    }

    d2d::terminate();
}