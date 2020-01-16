#pragma once

#define D2D_LINUX

#include <GLFW/glfw3.h>

namespace d2d {

int init();
void terminate();
struct window_t
{
private:
    GLFWwindow* m_window;
public:
    uint32_t width, height;
    const char* title;
}

struct color_t
{
    double r, g, b, a;
}

namespace window {


    void set_onclick_function(
        void(*onclick_function)(window_t&));

    void set_background(window_t& window, color_t& color);

    void set_main_window(window_t& window);

    bool should_close(window_t& window);

    void poll_events(window_t& window);
}

namespace draw {
    void rect(double x, double y, 
            double width, double height, double rotation);
}


}