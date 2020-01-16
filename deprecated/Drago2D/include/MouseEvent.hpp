#pragma once

#include "Event.hpp"

namespace d2d
{
    EVENT_SUBCLASS_DECLARATION(Mouse, MovedEvent)
	{
	private:
		float mMouseX, mMouseY;
	public:
		MouseMovedEvent(float x, float y)
			: mMouseX(x), mMouseY(y) {}

		inline float GetX() const { return mMouseX; }
		inline float GetY() const { return mMouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << mMouseX << ", " << mMouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	EVENT_SUBCLASS_DECLARATION(Mouse, ScrolledEvent)
	{
	private:
		float mXOffset, mYOffset;
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: mXOffset(xOffset), mYOffset(yOffset) {}

		inline float GetXOffset() const { return mXOffset; }
		inline float GetYOffset() const { return mYOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	EVENT_SUBCLASS_DECLARATION(Mouse, ButtonEvent)
	{
	protected:
		MouseButtonEvent(int button)
			: mButton(button) {}
		int mButton;
	public:
		inline int GetMouseButton() const { return mButton; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	};

    #define MOUSE_BUTTON_DECLARATION(type, name) class D2D_API type ##name : public MouseButtonEvent

	MOUSE_BUTTON_DECLARATION(Mouse, ButtonPressedEvent)
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << mButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	MOUSE_BUTTON_DECLARATION(Mouse, ButtonReleasedEvent)
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << mButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}