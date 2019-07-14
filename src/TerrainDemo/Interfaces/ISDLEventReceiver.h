#pragma once

#include <SDL.h>

namespace TerrainDemo
{
    namespace interfaces
    {
        class ISDLEventReceiver
        {
        public:
            virtual bool processSDLEvent(SDL_Event const&) = 0;
        };
    }
}
