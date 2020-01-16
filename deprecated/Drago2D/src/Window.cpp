#include "GLEW/glew.h"
#include "Window.hpp"


#include "Log.hpp"

namespace d2d
{
    Window::Window(int w, int h, const std::string &tit)
        : mWidth(w), mHeight(h), mTitle(tit)
    {
        
        if (!glfwInit())
        {
            D2D_LOG_CORE_CRITICAL("GLFW Failed to initialize!");
            exit(1);
        }

        D2D_LOG_CORE_INFO("Initialized GLFW!");
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_SAMPLES, 8);


        mWindow = glfwCreateWindow(w, h, tit.c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(mWindow);

        D2D_LOG_CORE_INFO("Created window!");

        if (glewInit() != GLEW_OK)
        {
            D2D_LOG_CORE_CRITICAL("GLEW Failed to initialize!");
            exit(1);
        }    
        D2D_LOG_CORE_INFO("Initialized GLEW");

        glfwSetWindowUserPointer(mWindow, (void *)&mEvents);

        glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods){
            
            KeyEvent *e;

            switch (action)
            {
            case GLFW_PRESS:
                e = new KeyTypedEvent(key);
                break;
            case GLFW_REPEAT:
                e = new KeyPressedEvent(key);
                break;
            case GLFW_RELEASE:
                e = new KeyReleasedEvent(key);
                break;            
            default:
                break;
            }

            auto events = (std::vector<Event *> *)(glfwGetWindowUserPointer(window));

            events->push_back(e);
        });

        glfwSetMouseButtonCallback(mWindow, (GLFWmousebuttonfun)[](GLFWwindow* window, int button, int action, int mods){
            MouseButtonEvent *e;

            switch (action)
            {
            case GLFW_PRESS:
                e = new MouseButtonPressedEvent(button);
                break;
            case GLFW_RELEASE:
                e = new MouseButtonReleasedEvent(button);
                break;            
            default:
                break;
            }

            auto events = (std::vector<Event *> *)(glfwGetWindowUserPointer(window));

            events->push_back(e);

        });

        glfwSetCursorPosCallback(mWindow, [](GLFWwindow *window, double xPos, double yPos){
            MouseMovedEvent *e;

            auto events = (std::vector<Event *> *)(glfwGetWindowUserPointer(window));
            e = new MouseMovedEvent(xPos, yPos);
            events->push_back(e);
        });

        glfwSetScrollCallback(mWindow, [](GLFWwindow *window, double xOff, double yOff){
            MouseScrolledEvent *e;

            auto events = (std::vector<Event *> *)(glfwGetWindowUserPointer(window));
            e = new MouseScrolledEvent(xOff, yOff);
            events->push_back(e); 
        });

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Window::~Window()
    {
        ClearEvents();
        glfwTerminate();
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(mWindow);
    }

    void Window::Update()
    {
        glfwSwapBuffers(mWindow);
        glfwGetCursorPos(mWindow, &mouseX, &mouseY);
        ClearEvents();
        glfwPollEvents();
    }

    void Window::ClearEvents()
    {
        for (auto e : mEvents)
            delete e;
        mEvents.clear();
    }

}