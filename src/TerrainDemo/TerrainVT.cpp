
#include <TerrainDemo/TerrainVT.h>
#include <TerrainDemo/core/Utils.h>

#include <geUtil/Text.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace ge::gl;
using namespace TerrainDemo;
using namespace TerrainDemo::core;
using namespace TerrainDemo::interfaces;

TerrainVT::TerrainVT()
{
}

void TerrainVT::drawSetUp()
{
    // initiation of gl
    gl->glEnable(GL_DEPTH_TEST);
    gl->glDepthFunc(GL_LEQUAL);
    gl->glDisable(GL_CULL_FACE);
    gl->glClearColor(0, 0, 0, 0);

    // create and conpile program
    program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(VERTEX_SHADER)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(FRAGMENT_SHADER))
    );

    program->setMatrix4fv("projectionMatrix", glm::value_ptr(_camera->getProjectionMatrix()));

    // BEGIN temporal test delete when proper model/terrain is loaded -------------------------------
        std::vector<float> vertices = {
            -1.f,  0.f,  0.f,
             1.f,  0.f,  0.f,
             0.f, -1.f,  0.f,
             0.f,  1.f,  0.f,
             0.f,  0.f, -1.f,
             0.f,  0.f,  1.f,
        };

        std::vector<float> vertColors = {
            1.f, 0.f, 0.f,
            1.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            0.f, 1.f, 0.f,
            0.f, 0.f, 1.f,
            0.f, 0.f, 1.f,
        };

        std::vector<unsigned> indices = {
            0,1,
            2,3,
            4,5
        };

        positions = std::make_shared<ge::gl::Buffer>(vertices.size() * sizeof(float), vertices.data());
        colors = std::make_shared<ge::gl::Buffer>(vertColors.size() * sizeof(float), vertColors.data());
        elementBuffer = std::make_shared<ge::gl::Buffer>(indices.size() * sizeof(int), indices.data());

        VAO = std::make_shared<ge::gl::VertexArray>();

        VAO->bind();
        VAO->addElementBuffer(elementBuffer);
        VAO->addAttrib(positions, 0, 3, GL_FLOAT);
        VAO->addAttrib(colors, 1, 3, GL_FLOAT);
        VAO->unbind();

        //_camera->setCameraPosition(glm::vec3{0.f, 1.f, 5.f});
    // END temporal test delete when proper model/terrain is loaded -------------------------------
}

void TerrainVT::draw()
{
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!_scene)
        return;

    if (_camera->hasViewChanged())
        program->setMatrix4fv("viewMatrix", glm::value_ptr(_camera->getViewMatrix()));

    program->use();

    VAO->bind();
    gl->glDrawElements(GL_LINES, elementBuffer->getSize(), GL_UNSIGNED_INT, nullptr);
}

void TerrainVT::setScene(shared_ptr<Scene> scene)
{
    _scene = static_pointer_cast<TerrainScene>(scene);

    // maybe analyze scene and convert to VAOS ...
}
