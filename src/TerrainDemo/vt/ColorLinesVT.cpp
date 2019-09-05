
#include <TerrainDemo/vt/ColorLinesVT.h>
#include <geGL/geGL.h>
#include <geUtil/Text.h>

using namespace std;
using namespace TerrainDemo::vt;

void ColorLinesVT::initGlProgram()
{
    _program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_VERT_COLOR_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_VERT_COLOR_FRAGMENT))
    );
}
