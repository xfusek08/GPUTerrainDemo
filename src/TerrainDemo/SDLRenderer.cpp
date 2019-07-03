
#include <TerrainDemo/SDLRenderer.h>
#include <TerrainDemo/utils.h>

using namespace std;
using namespace TerrainDemo;

SDLRenderer::SDLRenderer(
    std::shared_ptr<sdl2cpp::Window> window,
    std::shared_ptr<sdl2cpp::MainLoop> mainLoop
) {
    this->_window = window;
    this->_mainLoop = mainLoop;

    // bind callbacks
    this->_mainLoop->setEventHandler(bind(&SDLRenderer::update, this, placeholders::_1));
    this->_mainLoop->setIdleCallback(bind(&SDLRenderer::draw, this));

    // create window and make current context
    this->_window->createContext("rendering");
    this->_mainLoop->addWindow("primaryWindow", window);
    this->_window->makeCurrent("rendering");

    this->init();
}

SDLRenderer::~SDLRenderer() {}

void SDLRenderer::run()
{
    GPTR_LOG_Debug("Starting renderer.");
    (*this->_mainLoop)();
    GPTR_LOG_Debug("Renderer ended.");
}

void SDLRenderer::init()
{
    GPTR_LOG_Debug("SDLRenderer::init()");
}

bool SDLRenderer::update(SDL_Event const& event)
{
    GPTR_LOG_Debug("SDLRenderer::update()");
     if (event.type == SDL_WINDOWEVENT)
     {
         if (event.window.event == SDL_WINDOWEVENT_CLOSE)
         {
             this->_mainLoop->stop();
         }
     }
    return true;
}

void SDLRenderer::draw()
{
    GPTR_LOG_Debug("SDLRenderer::draw()");
}
