#pragma once

#include <list>
#include <SDL.h>

namespace  gpd
{
    namespace sdl
    {
        class SDLPerformance
        {
        public:
            static const unsigned FPS_CAP = 60;
            static const unsigned HISTORY_LEN = 60;

            SDLPerformance();
            void frame();

            inline bool  IsFramesCounted() const { return isFramesCounted; }
            inline float getFrames()       const { return previousCounted; }

            void getHistory(float *buffer, unsigned size = SDLPerformance::HISTORY_LEN) const;

        protected:
            std::list<float> history;

            bool isFramesCounted = false;
            float previousCounted = 0.0f;

            Uint32
                frameCnt = 0,
                frameCountingTimeMs = 0,
                msPerFrame = 0,
                frameBeginTime = 0,
                previousBeginTime = 0;

            void historyAdd(float frames);
        };
    }
}
