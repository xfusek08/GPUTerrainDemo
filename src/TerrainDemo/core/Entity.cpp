#pragma once

#include <TerrainDemo/core/Entity.h>

using namespace std;
using namespace ge::gl;
using namespace TerrainDemo::core;

Entity::Entity()
{
    // simple exemplar triangle
    Entity(
        {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
        },
        {
            0, 1, 2
        }
    );
}

Entity::Entity(std::vector<float> verticies, std::vector<unsigned> indicies) :
    _verticies(verticies),
    _indicies(indicies)
{}



void Entity::initVao(shared_ptr<Context> gl)
{
    _bufferContainer.empty();
    vao = make_shared<VertexArray>(gl->getFunctionTable());
    vao->bind();
    defineVaoAttributes();
    vao->unbind();
}

void Entity::defineVaoAttributes()
{
    vao->addElementBuffer(newVaoBuffer(_indicies));
    vao->addAttrib(newVaoBuffer(_verticies), 0, 3, GL_FLOAT);
}
