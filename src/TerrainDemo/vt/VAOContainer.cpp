
#include <TerrainDemo/vt/VAOContainer.h>
#include <geGL/geGL.h>

using namespace std;
using namespace TerrainDemo::vt;

VAOContainer::VAOContainer(shared_ptr<ge::gl::Context> gl)
{
    vao = make_shared<ge::gl::VertexArray>(gl->getFunctionTable());
}
