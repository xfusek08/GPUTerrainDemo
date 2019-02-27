#include <iostream>

#include <QtGui/QOpenGLContext>
#include <geGL/geGL.h>
#include <geCore/Text.h>
#include <GPUTerrain.h>

#include <OpenGLWindow.h>

using namespace gpuTerrain;

//! [ctor]
TerrainDemo::OpenGLWindow::OpenGLWindow(QWindow *parent) :
    QWindow(parent),
    initialized(false),
    context(nullptr)
{
  setSurfaceType(QWindow::OpenGLSurface); //this needs to be set otherwise makeCurrent and other gl context related functions will fail
  surfaceFormat.setVersion(4, 5);
  surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);
}
//! [ctor]

TerrainDemo::OpenGLWindow::~OpenGLWindow()
{
}

/**
 * Create OpenGL context with Qt with appropriate surface format.
 * Then initialize geGL and creating geGL context wrapper with OpenGL
 * functions entry points. Also prints out the GL_VERSION string.
 */
void TerrainDemo::OpenGLWindow::initialize()
{
  if (initialized)
    return;
  //! [qt_context]
  if (!context)
  {
    context = new QOpenGLContext(this);
    context->setFormat(surfaceFormat);
    bool success = context->create();
    if (!success)
    {
      //fail gracefully
    }
  }
  //! [qt_context]

  //! [makeCurrent]
  //let's say to the OS that we want to work with this context
  context->makeCurrent(this);
  //! [makeCurrent]

  //! [geGL_init]
  /*GPUEngine Init*/
  ge::gl::init();
  gl = std::make_shared<ge::gl::Context>();

  //! [geGL_init]

  //! [shaders]

  std::shared_ptr<ge::gl::Shader> vertexShader = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::core::loadTextFile(VERTEX_SHADER));
  std::shared_ptr<ge::gl::Shader> fragmentShader = std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::core::loadTextFile(FRAGMENT_SHADER));
  shaderProgram = std::make_shared<ge::gl::Program>(vertexShader, fragmentShader);

  //! [shaders]

  // craete terrain instance
  std::shared_ptr<GPUTerrain> terrain = std::make_shared<GPUTerrain>();

  terrain->generate();

  //! [buffer_ctor]

  positions = std::make_shared<ge::gl::Buffer>(
    terrain->getVertices().size() * sizeof(float),
    terrain->getVertices().data()
  );

  colors = std::make_shared<ge::gl::Buffer>(
    terrain->getColors().size() * sizeof(float),
    terrain->getColors().data()
  );

  elementBuffer = std::make_shared<ge::gl::Buffer>(
    terrain->getIndicies().size() * sizeof(int),
    terrain->getIndicies().data()
  );

  //! [buffer_ctor]

  //! [VAO]

  VAO = std::make_shared<ge::gl::VertexArray>();

  VAO->bind();
  VAO->addElementBuffer(elementBuffer);
  VAO->addAttrib(positions, 0, 3, GL_FLOAT);
  VAO->addAttrib(colors, 1, 3, GL_FLOAT);
  VAO->unbind();

  //! [VAO]

  initialized = true;
}

//! [render]

void TerrainDemo::OpenGLWindow::render()
{
  const qreal retinaScale = devicePixelRatio();
  gl->glViewport(0, 0, width() * retinaScale, height() * retinaScale);
  gl->glClearColor(.392, .584, 0.929, 1.0);
  gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  shaderProgram->use();
  VAO->bind();
  gl->glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

  printError(); // checks for gl error and if any prints it to stdout

  context->swapBuffers(this);
}

//! [render]

void TerrainDemo::OpenGLWindow::printError() const
{
  auto err = this->gl->glGetError();
  if (err != GL_NO_ERROR)
  {
    std::cout << err << std::endl;
  }
}

//! [renderNow]
void TerrainDemo::OpenGLWindow::renderNow()
{
  if (!isExposed())
    return;
  if (!initialized)
    initialize();

  //context->makeCurrent(this);
  //context never got released so no need to make it current again

  render(); //do the simple rendering

  //release context only if necessary
}
//! [renderNow]

//! [eventFilter]
bool TerrainDemo::OpenGLWindow::event(QEvent *event)
{
  switch (event->type())
  {
    case QEvent::UpdateRequest:
      renderNow();
      return true;
    default:
      return QWindow::event(event);
  }
}
//! [eventFilter]

//! [expose]
void TerrainDemo::OpenGLWindow::exposeEvent(QExposeEvent *event)
{
  if (isExposed())
  {
    renderNow();
  }
}
//! [expose]