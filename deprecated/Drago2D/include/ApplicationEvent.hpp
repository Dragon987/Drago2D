#pragma once

#include "Event.hpp"


namespace d2d
{
    EVENT_SUBCLASS_DECLARATION(Window, ResizeEvent)
    {
    private:
        unsigned int mWidth, mHeight;

    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : mWidth(width), mHeight(height) {}

        inline unsigned int GetWidth() const { return mWidth; }
        inline unsigned int GetHeight() const { return mHeight; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << mWidth << ", " << mHeight;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize);
        EVENT_CLASS_CATEGORY(EventCategoryApplication);
    };

    EVENT_SUBCLASS_DECLARATION(Window, CloseEvent)
    {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose);
        EVENT_CLASS_CATEGORY(EventCategoryApplication);
    };

    EVENT_SUBCLASS_DECLARATION(App, TickEvent)
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	EVENT_SUBCLASS_DECLARATION(App, UpdateEvent)
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	EVENT_SUBCLASS_DECLARATION(App, RenderEvent)
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}