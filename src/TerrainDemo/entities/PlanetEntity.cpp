
#include <TerrainDemo/entities/PlanetEntity.h>
#include <TerrainDemo/vt/VAOContainer.h>
#include <geGL/geGL.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::entities;

PlanetEntity::PlanetEntity(vt::VTType vtType) : Entity(vtType)
{
    _indicies  = {};
    _verticies = {};
}

void PlanetEntity::loadToVaoElement(shared_ptr<vt::VAOContainer> vaoElem)
{
}
