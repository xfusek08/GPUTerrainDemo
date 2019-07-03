
#include <memory>
#include <string>

#include <geGL/geGL.h>
#include <geGL/StaticCalls.h>

#include <TerrainDemo/Log.h>
#include <TerrainDemo/utils.h>
#include <TerrainDemo/Application.h>

using namespace std;
using namespace TerrainDemo;
using namespace ge::ad;

Application::Application() {}

Application::~Application() {}

int Application::init()
{
    GPTR_LOG_INFO("Application initiating ...");

    this->_mainLoop = make_shared<SDLMainLoop>();
    this->_window = make_shared<SDLWindow>();

    this->_mainLoop->setEventHandler(std::bind(&Application::update, this, std::placeholders::_1));
    this->_mainLoop->setIdleCallback(std::bind(&Application::draw, this));

    if (!this->_window->createContext("rendering"))
    {
        GPTR_LOG_ERROR("Error: Can not create OpenGL context.");
        return false;
    }

    this->_mainLoop->addWindow("primaryWindow", this->_window);
    this->_window->makeCurrent("rendering");

    ge::gl::init();

    ge::gl::glEnable(GL_DEPTH_TEST);
    ge::gl::glDepthFunc(GL_LEQUAL);
    ge::gl::glDisable(GL_CULL_FACE);
    ge::gl::glClearColor(0, 1, 0, 1);

    auto glProgram = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, VERTEX_SHADER),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, FRAGMENT_SHADER
    ));

    GPTR_LOG_INFO("Application initialized.");
    return true;
}

int Application::run()
{
    GPTR_LOG_INFO("Application running ...");

    (*this->_mainLoop)();

    GPTR_LOG_INFO("Application end.");
    return 0;
}

bool Application::update(SDL_Event const& event)
{
    return true;
}

void Application::draw()
{
    ge::gl::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->_window->swap();
}
