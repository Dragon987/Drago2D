#pragma once

#include "d2dpch.h"

#include <GLFW/glfw3.h>

#include "Event.hpp"
#include "ApplicationEvent.hpp"
#include "KeyEvent.hpp"
#include "MouseEvent.hpp"





namespace d2d
{
    class Window
    {
    private:
        GLFWwindow *mWindow;
        int mWidth, mHeight;
        std::string mTitle;
        std::vector<Event *> mEvents;
        std::function<void(const Event &e)> mEventHandler;
        double mouseX, mouseY;
    
    private:

    public:

        struct WindowData
        {
            void(*evHandler)(const Event &e);
        };


        inline Window() {}
        Window(int width, int height, const std::string &title);
        ~Window();

        inline int GetWidth() { return mWidth; }
        inline int GetHeight() { return mHeight; }

        bool ShouldClose();
        void Update();

        inline std::tuple<float, float> GetMousePosition() { return std::tuple((float)mouseX, (float)mouseY); }

        inline float GetMousePositionX() { return (float)mouseX; }
        inline float GetMousePositionY() { return (float)mouseY; }

        void ClearEvents();
        inline std::vector<Event *> & GetEvents() { return mEvents; }

    };
}