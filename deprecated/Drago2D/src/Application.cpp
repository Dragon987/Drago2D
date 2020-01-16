#include "Application.hpp"
#include "Draw.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include "Log.hpp"


namespace d2d
{
    void Application::Run()
    {
        Setup();
        Translate();
        while(!mWindow->ShouldClose())
        {
            Update();
            for (auto e : (mWindow->GetEvents()))
                OnEvent(*e);
            mWindow->Update();
        }
    }

    Application::Application()
    {
        mWindow = new Window(640, 480, "Drago2D Game Window");
        mProjection = glm::ortho(0, 640, 480, 0);
    }

    Application::Application(int width, int height, const std::string &title)
    {
        mWindow = new Window(width, height, title.c_str());
        mProjection = glm::ortho(0, width, height, 0);
    }

    void Application::Translate(float left, float right, float bottom, float top) { mProjection = glm::ortho(left, right, bottom, top); }
    void Application::Translate(float x, float y) { mProjection = glm::ortho(-x, GetScreenWidth() - x, GetScreenHeight() - y, y); }
    void Application::Translate() { mProjection = glm::ortho(0, GetScreenWidth(), GetScreenHeight(), 0); }

    void Application::OnEvent(const Event &e)
    {
        D2D_LOG_INFO(e.ToString());
    }

    Application::~Application()
    {
        delete mWindow;
    }

    void Application::DrawRect(const float x, const float y, const float w, const float h, const Color& c)
    {
        renderer::Actor a(D2D_DYNAMIC_DRAW, c, 
                        renderer::transform_vertex_shader_file, renderer::transform_frag_shader_file,
                        { { x - w, y - h }, { x + w, y - h }, { x + w, y + h }, { x - w, y + h} });

        a.SetTransform(x, y, 0, 1, 1);

        a.Draw(mProjection, D2D_LINE_LOOP);
    }
}