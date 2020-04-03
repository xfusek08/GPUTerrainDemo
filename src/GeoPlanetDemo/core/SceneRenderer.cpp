#pragma once

#include <geGL/geGL.h>

#include <GeoPlanetDemo/core/SceneRenderer.h>
#include <GeoPlanetDemo/core/Camera.h>
#include <GeoPlanetDemo/core/Utils.h>

#include <GeoPlanetDemo/scene/Scene.h>

#include <GeoPlanetDemo/vt/VTFactory.h>

using namespace gpd::core;
using namespace gpd::scene;
using namespace gpd::vt;
using namespace std;

SceneRenderer::SceneRenderer(std::shared_ptr<ge::gl::Context> context, std::shared_ptr<Scene> scene) :
    gl(context),
    scene(scene)
{
    // gl->glClearColor(0, 0, 0, 0); // TODO: some kind of prepare method

    gl->glClearColor(0, 0, 255, 1);

    updateScene();
}

void SceneRenderer::updateScene()
{
    GPD_LOG_DEBUG("updateScene");
    for (auto element : scene->getElements()) {
        // vt type is not present
        if (element.isValid() && vts.find(element.vtType) == vts.end()) {
            auto vt = VTFactory::create(element.vtType, gl);
            GPD_ASSERT(vt != nullptr, "vt was not successfully created");
            if (vt != nullptr) {
                vts.emplace(element.vtType, vt);
            }
        }
    }

    // reload scene for each used vt, where vt load only belonging entities
    for (auto pair : vts) {
        auto vt = pair.second;
        vt->clean();
        vt->processScene(scene);
    }
}

void SceneRenderer::draw(std::shared_ptr<Camera> camera) const
{
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto pair : vts) {
        auto vt = pair.second;
        vt->drawSetUp();
        vt->draw(camera);
    }

    camera->acceptChange();
}
