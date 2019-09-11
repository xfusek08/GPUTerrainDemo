#pragma once

#include <TerrainDemo/entities/Entity.h>

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

Entity::Entity(vt::VTType vtType, std::vector<float> verticies, std::vector<unsigned> indicies) :
    _vtType(vtType),
    _verticies(verticies),
    _indicies(indicies)
{
}
