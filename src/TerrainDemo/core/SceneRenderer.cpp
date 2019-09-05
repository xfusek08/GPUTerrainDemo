#pragma once

#include <TerrainDemo/core/SceneRenderer.h>
#include <TerrainDemo/core/Camera.h>
#include <TerrainDemo/core/Utils.h>

#include <TerrainDemo/vt/VTFactory.h>

#include <geGL/geGL.h>

using namespace TerrainDemo::core;

SceneRenderer::SceneRenderer(std::shared_ptr<ge::gl::Context> context, std::shared_ptr<Scene> scene) :
	_gl(context),
	_scene(scene)
{
    updateScene();
}

void SceneRenderer::updateScene()
{
    // TD_LOG_DEBUG("updateScene");
    // foreach entity in scene, get vt instance by vt type on entity from vector
    // if there is none instance of the type, create it and store
    //
    // VTFactory
}

void SceneRenderer::draw(std::shared_ptr<Camera>) const
{
    _gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
