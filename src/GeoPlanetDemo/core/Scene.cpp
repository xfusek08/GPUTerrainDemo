
#include <GeoPlanetDemo/core/Scene.h>

using namespace std;
using namespace gpd;
using namespace gpd::core;

vector<shared_ptr<entities::Entity>> Scene::getEntities() const
{
    vector<shared_ptr<entities::Entity>> res;
    for (auto pair : entities) {
        res.push_back(pair.second);
    }
    return res;
}
