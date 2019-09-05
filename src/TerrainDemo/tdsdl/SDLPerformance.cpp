
#include <TerrainDemo/tdsdl/SDLPerformance.h>

using namespace TerrainDemo::tdsdl;

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

    _previousBeginTime = _beginTimeMs;
    _beginTimeMs = SDL_GetTicks();
    _frameCnt++;

    _frameCountingTimeMs += _beginTimeMs - _previousBeginTime;
    if (_frameCountingTimeMs >= 1000) {
        _framesCounted = true;
        _frameCountingTimeMs = 0;
    }
}

void SDLPerformance::capFps()
{
    auto frameEnd = SDL_GetTicks();
    if (_msPerFrame > (frameEnd - _beginTimeMs))
        SDL_Delay(_msPerFrame - frameEnd + _beginTimeMs);
}
