
#include <TerrainDemo/core/Scene.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::core;

vector<shared_ptr<entities::Entity>> Scene::getEntities() const
{
    vector<shared_ptr<entities::Entity>> res;
    for (auto pair : _entities) {
        res.push_back(pair.second);
    }
    return res;
}
