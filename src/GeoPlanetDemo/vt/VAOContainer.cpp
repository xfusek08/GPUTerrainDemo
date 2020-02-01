
#include <GeoPlanetDemo/vt/VAOContainer.h>
#include <geGL/geGL.h>

using namespace std;
using namespace gpd::vt;

VAOContainer::VAOContainer(shared_ptr<ge::gl::Context> gl)
{
    vao = make_shared<ge::gl::VertexArray>(gl->getFunctionTable());
}

void VAOContainer::bind()
{
    vao->bind();
}

void VAOContainer::unbind()
{
    vao->unbind();
}
