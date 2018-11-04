
#pragma once

#include <QtGui/QWindow>
#include <memory>

class QOpenGLPaintDevice;

namespace ge
{
  namespace gl
  {
    class Context;
    class Program;
    class VertexArray;
    class Buffer;
  }
}

namespace TerrainDemo
{
  /**
   * Basic QWindow subclass for simple OpenGL rendering.
   */
  class OpenGLWindow : public QWindow {

    Q_OBJECT // some wierd Qt macro magic ...

  public:
    explicit OpenGLWindow(QWindow *parent = 0);

    ~OpenGLWindow();

    virtual void render();
    virtual void initialize();

    static const std::string fragmentShaderSrc;

  public slots:

    void renderNow();

  protected:
    bool event(QEvent *event) override;
    void exposeEvent(QExposeEvent *event) override;
    void printError() const;

  private:
    bool initialized;

    static std::vector<float> trianglePos;
    static std::vector<float> triangleCol;
    static std::vector<int> indices;

    std::shared_ptr<ge::gl::Buffer> positions;
    std::shared_ptr<ge::gl::Buffer> colors;
    std::shared_ptr<ge::gl::Buffer> elementBuffer;

    std::shared_ptr<ge::gl::Context> gl;
    std::shared_ptr<ge::gl::Program> shaderProgram;
    std::shared_ptr<ge::gl::VertexArray> VAO;
    QOpenGLContext *context;
    QSurfaceFormat surfaceFormat;
  };
}
