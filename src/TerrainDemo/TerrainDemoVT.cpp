
#include <geGL/geGL.h>
#include <TerrainDemo/TerrainDemoVT.h>
#include <TerrainDemo/TDScene.h>
#include <TerrainDemo/core/Utils.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace ge::gl;
using namespace TerrainDemo;
using namespace TerrainDemo::Interfaces;


TerrainDemoVT::TerrainDemoVT()
{
}

void TerrainDemoVT::drawSetUp()
{
    std::vector<float> trianglePos = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    std::vector<float> triangleCol = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };

    std::vector<unsigned> indices = {
        0,1,2
    };

    positions = std::make_shared<ge::gl::Buffer>(trianglePos.size() * sizeof(float), trianglePos.data());
    colors = std::make_shared<ge::gl::Buffer>(triangleCol.size() * sizeof(float), triangleCol.data());
    elementBuffer = std::make_shared<ge::gl::Buffer>(indices.size() * sizeof(int), indices.data());

    VAO = std::make_shared<ge::gl::VertexArray>();

    VAO->bind();
    VAO->addElementBuffer(elementBuffer);
    VAO->addAttrib(positions, 0, 3, GL_FLOAT);
    VAO->addAttrib(colors, 1,3,GL_FLOAT);
    VAO->unbind();
}

void TerrainDemoVT::draw() const
{
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!_scene)
        return;

    program->use();
    VAO->bind();
    gl->glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT, nullptr);
}

void TerrainDemoVT::setScene(shared_ptr<IScene> scene)
{
    _scene = static_pointer_cast<TDScene>(scene);
}
