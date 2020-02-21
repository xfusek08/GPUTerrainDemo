#pragma once

#include <SDL.h>

namespace gpd
{
    namespace sdl
    {
        class SDLEventReceiverInterface
        {
        public:
            virtual bool processSDLEvent(SDL_Event const&) = 0;
            virtual void onFrameUpdate() = 0;
        };
    }
}
