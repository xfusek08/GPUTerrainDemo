
#include <TerrainDemo/vt/VAOContainer.h>
#include <geGL/geGL.h>

using namespace std;
using namespace TerrainDemo::vt;

VAOContainer::VAOContainer(shared_ptr<ge::gl::Context> gl)
{
    vao = make_shared<ge::gl::VertexArray>(gl->getFunctionTable());
}

void VAOContainer::addTexture(std::shared_ptr<ge::gl::Texture> texture)
{
    _textureContainer.push_back(texture);
}

void VAOContainer::bind()
{
    vao->bind();
    for(auto texture : _textureContainer) {
        texture->bind(0);
    }
}

void VAOContainer::unbind()
{
    vao->unbind();
}
