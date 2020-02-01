
#include <GeoPlanetDemo/sdl/SDLGlMainLoop.h>
#include <GeoPlanetDemo/core/Utils.h>

#include <SDL2CPP/Window.h>
#include <SDL2CPP/MainLoop.h>

#include <geGL/geGL.h>

using namespace std;
using namespace gpd::sdl;
using namespace gpd::interfaces;

SDLGlMainLoop::SDLGlMainLoop(int width, int height) :
    _windowWidth(width),
    _windowHeight(height)
{
    init();
}

SDLGlMainLoop::~SDLGlMainLoop() {}

void SDLGlMainLoop::init()
{
    if (isInitialized()) {
        GPD_ASSERT(false, "double SDLGlMainLoop init called!");
        return;
    }

    GPD_LOG_DEBUG("SDLGlMainLoop::init()");

    // init SDL window
    _window = make_shared<sdl2cpp::Window>(_windowWidth, _windowHeight);
    _mainLoop = make_shared<sdl2cpp::MainLoop>();

    // bind callbacks
    _mainLoop->setEventHandler(bind(&SDLGlMainLoop::update, this, placeholders::_1));
    _mainLoop->setIdleCallback(bind(&SDLGlMainLoop::draw, this));

    // create window and make current context
    _window->createContext("rendering", 430u); // 450 by default
    _mainLoop->addWindow("primaryWindow", _window);
    _window->makeCurrent("rendering");

    ge::gl::init();

    _gl = make_shared<ge::gl::Context>();

    _initialized = _gl != nullptr && _window != nullptr && _mainLoop != nullptr;
}

void SDLGlMainLoop::run()
{
    if (!isInitialized()) {
        GPD_ASSERT(_initialized, "Calling SDLGlMainLoop::run() on SDLGlMainLoop befor its initiation");
        return;
    }
    GPD_LOG_DEBUG("Starting renderer.");
    (*_mainLoop)();
    GPD_LOG_DEBUG("Renderer ended.");
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

	#ifdef GPD_DEBUG
    if (_performance.framesCounted())
        GPD_LOG_INFO("FPS: " << _performance.getFrames());
	#endif

    _window->swap();
}
