#pragma once

#include "Core.hpp"
#include "Renderer.hpp"
#include <GLEW/glew.h>
#include "Window.hpp"
#include "glm/glm.hpp"


namespace d2d
{
    class D2D_API Application
    {
    private:
        glm::mat4 mProjection{1.f};

    protected:
        Window *mWindow;

    protected:


    public:


    public:
        Application();
        Application(int width, int height, const std::string &title);

        Application(const Application& other) = delete;
        Application(const Application&& other) = delete;

        Application& operator=(const Application& other) = delete;
        Application&& operator=(const Application&& other) = delete;

        virtual ~Application();

        virtual void Setup() = 0;
        virtual void Update() = 0;
        virtual void OnEvent(const Event &e);

        void Run();

        inline int GetScreenWidth() { return mWindow->GetWidth(); }
        inline int GetScreenHeight() { return mWindow->GetHeight(); }
        inline float GetMousePositionX() { return mWindow->GetMousePositionX(); }
        inline float GetMousePositionY() { return mWindow->GetMousePositionY(); }

        void Translate(float left, float right, float bottom, float top);
        void Translate(float x, float y);
        void Translate();

        inline std::tuple<float, float> GetMousePosition() { return mWindow->GetMousePosition(); }

        inline void Background(float r, float g, float b, float a)
        {
            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void DrawRect(const float x, const float y, const float w, const float h, const Color& c);

    };

    Application * CreateApplication();

}