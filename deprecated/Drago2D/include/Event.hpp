#pragma once

#include "Core.hpp"

#include "d2dpch.h"

namespace d2d
{

    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = D2D_BIT(0),
        EventCategoryInput = D2D_BIT(1),
        EventCategoryKeyboard = D2D_BIT(2),
        EventCategoryMouse = D2D_BIT(3),
        EventCategoryMouseButton = D2D_BIT(4)
    };

    //Macros used for speeding up Events development.

    #define EVENT_CLASS_TYPE(type)  virtual const char * GetName() const override { return #type; } \
                                    static EventType GetStaticType() { return EventType::type; } \
                                    virtual EventType GetEventType() const override { return GetStaticType(); } 
    
    #define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    // First argument is first part of EventType and second arg is second part of the name. Look at other Event files for clarification
    #define EVENT_SUBCLASS_DECLARATION(type, name) class D2D_API type ##name : public Event

    class D2D_API Event
    {
    protected:
        bool mHandled = false;

    public:
        virtual EventType GetEventType() const = 0;
        virtual int GetCategoryFlags() const = 0;

        virtual const char * GetName() const = 0;
        virtual std::string ToString() const { return GetName(); }

        inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
    };

    inline std::ostream & operator<<(std::ostream &os, const Event &e)
    {
        return os << e.ToString();
    }
}