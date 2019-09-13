#pragma once

#include <TerrainDemo/entities/Entity.h>
#include <TerrainDemo/vt/VAOContainer.h>
#include <geGL/geGL.h>

using namespace std;
using namespace ge::gl;
using namespace TerrainDemo;
using namespace TerrainDemo::entities;

Entity::Entity(vt::VTType vtType) :
    // simple exemplar triangle
	Entity(
        vtType,
        {
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             0.0f,  1.0f, 0.0f,
        },
        {
            0, 1, 2
        }
	)
{
}

Entity::Entity(vt::VTType vtType, vector<float> verticies, vector<unsigned> indicies) :
    _vtType(vtType),
    _verticies(verticies),
    _indicies(indicies)
{
}

void Entity::loadToVaoElement(shared_ptr<vt::VAOContainer> vaoElem)
{
    vaoElem->vao->addElementBuffer(vaoElem->newBuffer(getIndieces()));
    vaoElem->vao->addAttrib(vaoElem->newBuffer(getVerticies()), 0, 3, GL_FLOAT);
	vaoElem->indexSize = getIndieces().size();
}