
#include <TerrainDemo/TerrainScene.h>
#include <TerrainDemo/TerrainEntity.h>
#include <TerrainDemo/AxisEntity.h>

using namespace std;
using namespace TerrainDemo;

TerrainScene::TerrainScene() : Scene()
{
    _entities.push_back(make_shared<TerrainEntity>());
    _entities.push_back(make_shared<AxisEntity>());
}
