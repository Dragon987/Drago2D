#pragma once

#include "Event.hpp"

namespace d2d
{
    EVENT_SUBCLASS_DECLARATION(Key, Event)
    {
    protected:
        int mKeyCode;
        KeyEvent(int keyCode) : mKeyCode(keyCode) {}
    public:
        inline int GetKeyCode() const { return mKeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    };

    #define KEY_EVENT_DECLARATION(type, name) class D2D_API type ##name : public KeyEvent

    KEY_EVENT_DECLARATION(Key, PressedEvent)
    {
    public:
        KeyPressedEvent(int keyCode)
            : KeyEvent(keyCode) {}

        EVENT_CLASS_TYPE(KeyPressed)
    };

    KEY_EVENT_DECLARATION(Key, ReleasedEvent)
    {
    public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << mKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
    };

    KEY_EVENT_DECLARATION(Key, TypedEvent)
    {
    public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << mKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
    };
}