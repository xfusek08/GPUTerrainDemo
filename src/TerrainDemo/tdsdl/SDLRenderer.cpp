
#include <geGL/geGL.h>

#include <TerrainDemo/tdsdl/SDLRenderer.h>
#include <TerrainDemo/core/Utils.h>

using namespace std;
using namespace TerrainDemo::tdsdl;
using namespace TerrainDemo::interfaces;

SDLRenderer::SDLRenderer(
    std::shared_ptr<sdl2cpp::Window> window,
    std::shared_ptr<sdl2cpp::MainLoop> mainLoop,
    std::shared_ptr<IVisualizationTechnique> vt
) :
    _window(window),
    _mainLoop(mainLoop),
    _vt(vt),
    _gl(nullptr)
{
}

SDLRenderer::~SDLRenderer() {}

void SDLRenderer::init()
{
    GPTR_LOG_Debug("SDLRenderer::init()");

    // bind callbacks
    _mainLoop->setEventHandler(bind(&SDLRenderer::update, this, placeholders::_1));
    _mainLoop->setIdleCallback(bind(&SDLRenderer::draw, this));

    // create window and make current context
    _window->createContext("rendering");
    _mainLoop->addWindow("primaryWindow", _window);
    _window->makeCurrent("rendering");

    ge::gl::init();
    _gl = make_shared<ge::gl::Context>();
    setVT(_vt);

    _initialized = true;
}

void SDLRenderer::run()
{
    if (!_initialized) {
        GPTR_ASSERT(_initialized, "Calling Run on SDLRenderer befor its initiation");
        return;
    }
    if (_vt == nullptr) {
        GPTR_ASSERT(_initialized, "Cannot run SDLRenderer without visualization technique");
        return;
    }

    GPTR_LOG_Debug("Starting renderer.");
    _vt->drawSetUp();
    (*_mainLoop)();
    GPTR_LOG_Debug("Renderer ended.");
}

void SDLRenderer::addEventReceiver(std::shared_ptr<ISDLEventReceiver> receiver)
{
    _eventReceivers.push_back(receiver);
}

void SDLRenderer::setVT (shared_ptr<IVisualizationTechnique> vt)
{
    _vt = vt;
    _vt->gl = _gl;
}

bool SDLRenderer::update(SDL_Event const& event)
{
    if (event.type == SDL_WINDOWEVENT)
        if (event.window.event == SDL_WINDOWEVENT_CLOSE)
            _mainLoop->stop();

    for (auto eventReceiver : _eventReceivers)
        if (eventReceiver->processSDLEvent(event))
            break;

    return true;
}

void SDLRenderer::draw()
{
    _performance.frame();

    for (auto eventReceiver : _eventReceivers)
        eventReceiver->onFrameUpdate();

    _vt->draw();

    if (_performance.framesCounted()) 
        GPTR_LOG_Debug("FPS: " << _performance.getFrames());

    _performance.capFps();

    _window->swap();
}
