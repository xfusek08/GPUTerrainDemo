
#include <GeoPlanetDemo/sdl/SDLPerformance.h>

using namespace gpd::sdl;

SDLPerformance::SDLPerformance()
{
    _msPerFrame = 1000 / SDLPerformance::FPS_CAP;
}

void SDLPerformance::frame()
{
    if (_framesCounted) {
        _framesCounted = false;
        _frameCnt = 0;
    }

    auto frameEndTime = SDL_GetTicks();

    if (_msPerFrame > (frameEndTime - _frameBeginTime)) {
        SDL_Delay(_msPerFrame - frameEndTime + _frameBeginTime);
    }

    _previousBeginTime = _frameBeginTime;
    _frameBeginTime = SDL_GetTicks();

    _frameCountingTimeMs += _frameBeginTime - _previousBeginTime;

    _frameCnt++;

    if (_frameCountingTimeMs >= 1000) {
        _framesCounted = true;
        _frameCountingTimeMs = 0;
    }
}
