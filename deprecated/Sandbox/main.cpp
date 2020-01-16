#include <iostream>

#include <Drago2D.hpp>


class Sandbox : public d2d::Application
{
public:
    Sandbox(int w = 640, int h = 480, const std::string &title = "Sandbox")
        : Application(w, h, title)
    {
    }


    void Setup() override
    {        
    }

    void Update() override
    {
        Background(0, 0, 0, 1);
        DrawRect(200, 200, 100, 100, { 1, 0, 0, 1 });
    }

    void OnEvent(const d2d::Event &e) override
    {
    }

    ~Sandbox()
    {
    }

};

d2d::Application * d2d::CreateApplication()
{
    return new Sandbox();
}