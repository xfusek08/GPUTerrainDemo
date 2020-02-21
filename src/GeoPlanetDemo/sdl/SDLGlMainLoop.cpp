
#include <GeoPlanetDemo/sdl/SDLGlMainLoop.h>
#include <GeoPlanetDemo/core/Utils.h>

#include <SDL2CPP/Window.h>
#include <SDL2CPP/MainLoop.h>

#include <geGL/geGL.h>

using namespace std;
using namespace gpd::sdl;
using namespace gpd::interfaces;

SDLGlMainLoop::SDLGlMainLoop(int width, int height) :
    windowWidth(width),
    windowHeight(height)
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
    window = make_shared<sdl2cpp::Window>(windowWidth, windowHeight);
    mainLoop = make_shared<sdl2cpp::MainLoop>();

    // bind callbacks
    mainLoop->setEventHandler(bind(&SDLGlMainLoop::update, this, placeholders::_1));
    mainLoop->setIdleCallback(bind(&SDLGlMainLoop::draw, this));

    // create window and make current context
    window->createContext("rendering", 430u); // 450 by default
    mainLoop->addWindow("primaryWindow", window);
    window->makeCurrent("rendering");

    ge::gl::init();

    gl = make_shared<ge::gl::Context>();

    initialized = gl != nullptr && window != nullptr && mainLoop != nullptr;
}

void SDLGlMainLoop::run()
{
    if (!isInitialized()) {
        GPD_ASSERT(initialized, "Calling SDLGlMainLoop::run() on SDLGlMainLoop befor its initiation");
        return;
    }
    GPD_LOG_DEBUG("Starting renderer.");
    (*mainLoop)();
    GPD_LOG_DEBUG("Renderer ended.");
}

void SDLGlMainLoop::addEventReceiver(shared_ptr<SDLEventReceiverInterface> receiver)
{
    eventReceivers.push_back(receiver);
}

void SDLGlMainLoop::setEventHandler(function<bool(SDL_Event const&)> const& handler)
{
    eventHandler = handler;
}

void SDLGlMainLoop::setDrawCallback(function<void()> const& callback)
{
    drawCallback = callback;
}

bool SDLGlMainLoop::update(SDL_Event const& event)
{
    for (auto eventReceiver : eventReceivers)
        if (eventReceiver->processSDLEvent(event))
            break;

    if (eventHandler != nullptr)
        eventHandler(event);

    return true;
}

void SDLGlMainLoop::draw()
{
    performance.frame();

    for (auto eventReceiver : eventReceivers)
        eventReceiver->onFrameUpdate();

    if (drawCallback != nullptr)
        drawCallback();

    #ifdef GPD_DEBUG
    if (performance.IsFramesCounted())
        GPD_LOG_INFO("FPS: " << performance.getFrames());
    #endif

    window->swap();
}
