
#include <QtGui/QGuiApplication>
#include <QtGui/QOpenGLContext>
#include <OpenGLWindow.h>

using namespace std;

int main(int argc, char **argv)
{
  QGuiApplication app(argc, argv);

  TerrainDemo::OpenGLWindow window;
  window.resize(640, 480);
  window.show();

  return app.exec();
}
