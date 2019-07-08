
#include <TerrainDemo/core/SDLRenderer.h>

#include <geGL/geGL.h>
#include <geUtil/Text.h>
#include <TerrainDemo/core/Utils.h>

using namespace std;
using namespace TerrainDemo::core;
using namespace TerrainDemo::Interfaces;

SDLRenderer::SDLRenderer(
    std::shared_ptr<sdl2cpp::Window> window,
    std::shared_ptr<sdl2cpp::MainLoop> mainLoop,
    std::shared_ptr<IVisualizationTechnique> vt
) : _window(window),
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
    _gl->glEnable(GL_DEPTH_TEST);
    _gl->glDepthFunc(GL_LEQUAL);
    _gl->glDisable(GL_CULL_FACE);
    _gl->glClearColor(0, 0, 0, 0);

    _program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(VERTEX_SHADER)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(FRAGMENT_SHADER))
    );

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

void SDLRenderer::setControls(shared_ptr<SDLControls> controls)
{
    _controls = controls;
}

void SDLRenderer::setVT (shared_ptr<IVisualizationTechnique> vt)
{
    _vt = vt;
    _vt->gl = _gl;
    _vt->program = _program;
    _vt->setScene(_scene);
}

void SDLRenderer::setScene (shared_ptr<IScene> scene)
{
    _scene = scene;
    _vt->setScene(_scene);
}

bool SDLRenderer::update(SDL_Event const& event)
{
    if (event.type == SDL_WINDOWEVENT)
        if (event.window.event == SDL_WINDOWEVENT_CLOSE)
            _mainLoop->stop();

    if (_controls != nullptr)
        _controls->processSDLEvent(event);
    return true;
}

void SDLRenderer::draw()
{
    _vt->draw();
    _window->swap();
}
