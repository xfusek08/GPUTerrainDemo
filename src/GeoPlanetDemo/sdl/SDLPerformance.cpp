
#include <GeoPlanetDemo/sdl/SDLPerformance.h>

using namespace gpd::sdl;

SDLPerformance::SDLPerformance()
{
    msPerFrame = 1000 / SDLPerformance::FPS_CAP;
}

void SDLPerformance::frame()
{
    if (isFramesCounted) {
        isFramesCounted = false;
    }

    auto frameEndTime = SDL_GetTicks();

    if (msPerFrame > (frameEndTime - frameBeginTime)) {
        SDL_Delay (msPerFrame - frameEndTime + frameBeginTime);
    }

    previousBeginTime = frameBeginTime;
    frameBeginTime = SDL_GetTicks();

    frameCountingTimeMs += frameBeginTime - previousBeginTime;

    frameCnt++;

    if (frameCountingTimeMs >= 1000) {
		previousCounted = float(frameCnt) + (1000.0f - float(frameCountingTimeMs)) / 1000;
        historyAdd(previousCounted);
        isFramesCounted = true;
        frameCountingTimeMs = 0;
        frameCnt = 0;
    }
}

void SDLPerformance::historyAdd(float frames)
{
    history.push_front(frames);
    history.resize(SDLPerformance::HISTORY_LEN, 0.0f);
}

void SDLPerformance::getHistory(float *buffer, unsigned size) const
{
    for (float val : history) {
        if (size == 0) {
            break;
        }
        buffer[size - 1] = val;
        size--;
    }
}
