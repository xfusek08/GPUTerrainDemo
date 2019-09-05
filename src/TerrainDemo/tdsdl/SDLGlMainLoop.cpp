
#include <TerrainDemo/tdsdl/SDLGlMainLoop.h>
#include <TerrainDemo/core/Utils.h>

#include <SDL2CPP/Window.h>
#include <SDL2CPP/MainLoop.h>

#include <geGL/geGL.h>

using namespace std;
using namespace TerrainDemo::tdsdl;
using namespace TerrainDemo::interfaces;

SDLGlMainLoop::SDLGlMainLoop()
{
    init();
}

SDLGlMainLoop::~SDLGlMainLoop() {}

void SDLGlMainLoop::init()
{
    if (isInitialized()) {
        TD_ASSERT(false, "double SDLGlMainLoop init called!");
        return;
    }

    TD_LOG_DEBUG("SDLGlMainLoop::init()");

    // init SDL window
    _window = make_shared<sdl2cpp::Window>();
    _mainLoop = make_shared<sdl2cpp::MainLoop>();

    // bind callbacks
    _mainLoop->setEventHandler(bind(&SDLGlMainLoop::update, this, placeholders::_1));
    _mainLoop->setIdleCallback(bind(&SDLGlMainLoop::draw, this));

    // create window and make current context
    _window->createContext("rendering");
    _mainLoop->addWindow("primaryWindow", _window);
    _window->makeCurrent("rendering");

    ge::gl::init();

    _gl = make_shared<ge::gl::Context>();

    _initialized = _gl != nullptr && _window != nullptr && _mainLoop != nullptr;
}

void SDLGlMainLoop::run()
{
    if (!isInitialized()) {
        TD_ASSERT(_initialized, "Calling SDLGlMainLoop::run() on SDLGlMainLoop befor its initiation");
        return;
    }
    TD_LOG_DEBUG("Starting renderer.");
    (*_mainLoop)();
    TD_LOG_DEBUG("Renderer ended.");
}

void SDLGlMainLoop::addEventReceiver(shared_ptr<SDLEventReceiverInterface> receiver)
{
    _eventReceivers.push_back(receiver);
}

void SDLGlMainLoop::setEventHandler(function<bool(SDL_Event const&)> const& handler)
{
    _eventHandler = handler;
}

void SDLGlMainLoop::setDrawCallback(function<void()> const& callback)
{
    _drawCallback = callback;
}

bool SDLGlMainLoop::update(SDL_Event const& event)
{
    if (event.type == SDL_WINDOWEVENT)
        if (event.window.event == SDL_WINDOWEVENT_CLOSE)
            _mainLoop->stop();

    for (auto eventReceiver : _eventReceivers)
        if (eventReceiver->processSDLEvent(event))
            break;

    if (_eventHandler != nullptr)
        _eventHandler(event);

    return true;
}

void SDLGlMainLoop::draw()
{
    _performance.frame();

    for (auto eventReceiver : _eventReceivers)
        eventReceiver->onFrameUpdate();

    if (_drawCallback != nullptr)
        _drawCallback();

	#ifdef TD_DEBUG
    if (_performance.framesCounted())
        TD_LOG_INFO("FPS: " << _performance.getFrames());
	#endif

    _performance.capFps();

    _window->swap();
}
