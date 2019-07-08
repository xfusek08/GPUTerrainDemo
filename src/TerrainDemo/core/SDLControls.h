#pragma once

#include <SDL.h>
#include <TerrainDemo/Interfaces/IControls.h>

namespace TerrainDemo
{
    namespace core
    {
        class SDLControls : public Interfaces::IControls
        {
        public:
            SDLControls();
            ~SDLControls();

            virtual void processSDLEvent(SDL_Event const& event);
        };

    } // namespace core
} // namespace TerrainDemo
