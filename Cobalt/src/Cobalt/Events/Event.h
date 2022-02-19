#pragma once

#include "Cobalt/Core/Core.h"

namespace Cobalt
{

	// Event types
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		//AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// Event Categories
	enum EventCategory : unsigned char
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

// Macros for implementing virtual event functions based on event type and category
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type; }\
								virtual EventType GetEventType() const override {return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual unsigned char GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		// Getter functions for events
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual unsigned char GetCategoryFlags() const = 0;
		// Get the name of the event
		virtual std::string ToString() const { return GetName(); }

		// Check if event is in a category
		inline bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}

		// Check if event has been handled
		inline bool IsHandled() const { return m_Handled; }

	private:
		bool m_Handled = false;
	};

	class EventDispatcher
	{

	};
}