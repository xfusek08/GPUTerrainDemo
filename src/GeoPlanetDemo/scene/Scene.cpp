
#include <GeoPlanetDemo/scene/Scene.h>

using namespace std;
using namespace gpd;
using namespace gpd::scene;

const vector<SceneElement> Scene::getElements() const
{
    if (elements.size() <= 0) {
        return {};
    }

    vector<SceneElement> result;
    result.reserve(elements.size());
    for (auto element : elements) {
        result.push_back(element.second);
    }
    return result;
}


SceneElement Scene::getElement(string name)
{
    auto it = elements.find(name);
    if (it != elements.end()) {
        return it->second;
    }
    return {};
}
