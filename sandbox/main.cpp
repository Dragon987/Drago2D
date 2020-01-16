

#include "../drago2d.hpp"

int main()
{
    if (d2d::init())
    {
        d2d::log::perror("d2d::init");
        exit(0);
    }

    d2d::window_t window(640, 480, "Sandbox");

    d2d::window::set_onclick_function([](d2d::window_t& window) {
        d2d::window::set_background(window, { 255, 0, 0 });
    });

    d2d::window::set_main_window(window);

    while (1)
    {
        if (d2d::window::should_close(window))
            break;
        
        d2d::draw::rect(200, 200, 80, 40, 3.14159 / 4.0);

        d2d::window::poll_events(window);
    }

    d2d::terminate();
}