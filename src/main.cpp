
#include <GeoPlanetDemo/Application.h>

int main(int argc, char **argv)
{
  // more complex entry point ?
  auto app = gpd::Application();
  int init = app.init();
  if (init != 1)
    return init;
  return app.run();
}
