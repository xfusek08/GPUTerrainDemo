#pragma once

#include <TerrainDemo/entities/Entity.h>
#include <TerrainDemo/vt/VAOContainer.h>
#include <geGL/geGL.h>

using namespace std;
using namespace ge::gl;
using namespace TerrainDemo;
using namespace TerrainDemo::entities;

Entity::Entity(vt::VTType vtType) : _vtType(vtType) {}

vector<float> Entity::getVerticies() const
{
    return {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };
}

vector<unsigned> Entity::getIndieces() const
{
    return {
        0, 1, 2
    };
}
