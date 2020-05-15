﻿#include "pch.h"
#include "Events.h"

namespace winrt::Component::implementation
{
    using namespace Windows::Foundation;

    event_token Events::SimpleEvent(EventHandler<int32_t> const& handler)
    {
        return m_simple.add(handler);
    }

    void Events::SimpleEvent(event_token const& cookie)
    {
        m_simple.remove(cookie);
    }

    void Events::RaiseSimpleEvent(int value)
    {
        m_simple(*this, value);
    }

    event_token Events::TypedEvent(TypedEventHandler<Component::Events, int32_t> const& handler)
    {
        return m_typed.add(handler);
    }

    void Events::TypedEvent(event_token const& cookie)
    {
        m_typed.remove(cookie);
    }

    void Events::RaiseTypedEvent(int value)
    {
        m_typed(*this, value);
    }

    event_token Events::CustomEvent(CustomDelegate const& handler)
    {
        return m_custom.add(handler);
    }

    void Events::CustomEvent(event_token const& cookie)
    {
        m_custom.remove(cookie);
    }

    void Events::RaiseCustomEvent(int value)
    {
        m_custom(value);
    }
}

namespace winrt::Component::factory_implementation
{
    using namespace Windows::Foundation;

    event_token Events::StaticEvent(EventHandler<int32_t> const& handler)
    {
        return m_static.add(handler);
    }

    void Events::StaticEvent(event_token const& cookie)
    {
        m_static.remove(cookie);
    }

    void Events::RaiseStaticEvent(int value)
    {
        m_static(nullptr, value);
    }

    std::atomic<int> Events::s_constructorCount;

    bool Events::TestStaticLifetime()
    {
        // Capture current reference count.
        AddRef();
        auto refcount = Release();

        // Reset constructor count.
        s_constructorCount = 0;

        auto self = make_self<Events>();
        if (self.get() != this)
        {
            return false;
        }
        self = nullptr;

        // Refcount should be unchanged.
        // Should not have been constructed spuriously.
        AddRef();
        auto new_refcount = Release();

        return refcount == new_refcount && s_constructorCount == 0;
    }
}
