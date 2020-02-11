#pragma once

#include <GeoPlanetDemo/core/SceneRenderer.h>
#include <GeoPlanetDemo/core/Scene.h>
#include <GeoPlanetDemo/core/Camera.h>
#include <GeoPlanetDemo/core/Utils.h>

#include <GeoPlanetDemo/vt/VTFactory.h>

#include <geGL/geGL.h>

using namespace gpd::core;
using namespace gpd::vt;
using namespace std;

SceneRenderer::SceneRenderer(std::shared_ptr<ge::gl::Context> context, std::shared_ptr<Scene> scene) :
	_gl(context),
	_scene(scene)
{
	_gl->glClearColor(0, 0, 0, 0); // TODO: some kind of prepare method

    updateScene();
}

void SceneRenderer::updateScene()
{
    GPD_LOG_DEBUG("updateScene");
	for (auto entity : _scene->getEntities()) {
		// vt type is not present
		if (_vts.find(entity->getVtType()) == _vts.end()) {
			auto vt = VTFactory::createVTFromType(_gl, entity->getVtType());
            GPD_ASSERT(vt != nullptr, "vt was not successfully created");
            if (vt != nullptr) {
			    _vts.emplace(entity->getVtType(), vt);
            }
		}
	}

	// reload scene for each used vt, where vt load only belonging entities
	for (auto pair : _vts) {
		auto vt = pair.second;
		vt->clean();
		vt->processScene(_scene);
	}
}

void SceneRenderer::draw(std::shared_ptr<Camera> camera) const
{
    _gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto pair : _vts) {
		auto vt = pair.second;
		vt->drawSetUp();
		vt->draw(camera);
	}

	camera->acceptChange();
}
