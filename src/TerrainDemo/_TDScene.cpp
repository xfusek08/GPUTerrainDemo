
#include <TerrainLib/Terrain.h>
#include <TerrainDemo/TDScene.h>
#include <TerrainDemo/AxisEntity.h>

#ifdef TD_DEBUG
#define GLM_ENABLE_EXPERIMENTAL
#include <TerrainDemo/core/Utils.h>
#include <glm/gtx/string_cast.hpp>
#endif

using namespace tl;
using namespace std;
using namespace TerrainDemo;

TDScene::TDScene() : Scene()
{
    _entities.push_back(make_shared<AxisEntity>());

    auto terrain = make_shared<Terrain>(20);
    for (auto face : terrain->getFaces()) {
        _entities.push_back(make_shared<core::Entity>(
            face->getMesh()->vertices,
            face->getMesh()->indicies
        ));
    }
}
