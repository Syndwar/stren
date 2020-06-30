#include "event_processor.h"

#include "SDL.h"

namespace stren
{
EventProcessor::EventProcessor()
{
}

const Event & EventProcessor::getEvent()
{
    m_event.clear();
    SDL_Event sdlEvent;
    const bool hasEvents = 1 == SDL_PollEvent(&sdlEvent);
    if (hasEvents)
    {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
            {
                m_event.type = EventType::SysQuit;
            }
            break;
            case SDL_MOUSEMOTION:
            {
                m_event.type = EventType::MouseMove;
                m_event.pos.set(sdlEvent.motion.x, sdlEvent.motion.y);
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                m_event.type = EventType::MouseDown;
                m_event.mouseButton = static_cast<Event::MouseButton>(sdlEvent.button.button);
                m_event.pos.set(sdlEvent.button.x, sdlEvent.button.y);
            }
            break;
            case SDL_MOUSEBUTTONUP:
            {
                m_event.type = EventType::MouseUp;
                m_event.mouseButton = static_cast<Event::MouseButton>(sdlEvent.button.button);
                m_event.pos.set(sdlEvent.button.x, sdlEvent.button.y);
            }
            break;
            case SDL_MOUSEWHEEL:
            {
                m_event.type = EventType::MouseWheel;
                m_event.wheel.set(sdlEvent.wheel.x, sdlEvent.wheel.y);
                int x, y;
                SDL_GetMouseState(&x, &y);
                m_event.pos.set(x, y);
            }
            break;
            case SDL_KEYDOWN:
            {
                m_event.type = EventType::KeyDown;
                m_event.key = SDL_GetKeyName(sdlEvent.key.keysym.sym);
                if (sdlEvent.key.keysym.mod & KMOD_ALT)
                {
                    m_event.mod = Event::KeyMod::Alt;
                }
                else if (sdlEvent.key.keysym.mod & KMOD_SHIFT)
                {
                    m_event.mod = Event::KeyMod::Shift;
                }
                else if (sdlEvent.key.keysym.mod & KMOD_CTRL)
                {
                    m_event.mod = Event::KeyMod::Control;
                }
            }
            break;
            case SDL_KEYUP:
            {
                m_event.type = EventType::KeyUp;
                m_event.key = SDL_GetKeyName(sdlEvent.key.keysym.sym);
                if (sdlEvent.key.keysym.mod & KMOD_ALT)
                {
                    m_event.mod = Event::KeyMod::Alt;
                }
                else if (sdlEvent.key.keysym.mod & KMOD_SHIFT)
                {
                    m_event.mod = Event::KeyMod::Shift;
                }
                else if (sdlEvent.key.keysym.mod & KMOD_CTRL)
                {
                    m_event.mod = Event::KeyMod::Control;
                }
            }
            break;
            case SDL_WINDOWEVENT:
            case SDL_SYSWMEVENT:
            default:
            {
                m_event.type = EventType::Unknown;
            }
            break;
        }
    }
    return m_event;
}

const Point & EventProcessor::getMousePos()
{
    int x(0);
    int y(0);
    SDL_GetMouseState(&x, &y);
    m_mousPos.set(x, y);
    return m_mousPos;
}
} // stren