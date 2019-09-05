#pragma once

#include <SDL.h>

namespace TerrainDemo
{
    namespace tdsdl
    {
        class SDLPerformance
        {
            const unsigned FPS_CAP = 60;

        public:
            SDLPerformance();
            void frame();
            void capFps();

            inline bool framesCounted() { return _framesCounted; }
            inline unsigned getFrames() { return _frameCnt; }
        protected:
            bool _framesCounted = false;
            Uint32
                _frameCnt = 0,
                _frameCountingTimeMs = 0,
                _msPerFrame = 0,
                _beginTimeMs = 0,
                _endTimeMs = 0,
                _previousBeginTime = 0;
        };
    }
}
