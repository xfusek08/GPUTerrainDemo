#pragma once

#include <GeoPlanetDemo/entities/Entity.h>
#include <GeoPlanetDemo/vt/VAOContainer.h>
#include <geGL/geGL.h>

using namespace std;
using namespace ge::gl;
using namespace gpd;
using namespace gpd::entities;

Entity::Entity(vt::VTType vtType) : vtType(vtType) {}

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

bool Entity::setVtType(vt::VTType type)
{
    if (type != vtType) {
        vtType = type;
        return true;
    }
    return false;
}