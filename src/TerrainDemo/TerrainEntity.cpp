
#include <TerrainDemo/TerrainEntity.h>

using namespace std;
using namespace tl;
using namespace TerrainDemo;
using namespace TerrainDemo::core;

TerrainEntity::TerrainEntity() : Entity()
{
    _terrain = make_shared<Terrain>();
    _terrain->generate();
    _verticies = _terrain->getVertices();
    _indicies = _terrain->getIndicies();
}
