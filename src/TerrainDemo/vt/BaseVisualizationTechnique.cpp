
#pragma once

#include <TerrainDemo/vt/BaseVisualizationTechnique.h>

#include <TerrainDemo/core/Camera.h>

#include <geGL/geGL.h>
#include <geUtil/Text.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::vt;
using namespace TerrainDemo::core;

BaseVisualizationTechnique::BaseVisualizationTechnique(shared_ptr<ge::gl::Context> gl) : _gl(gl)
{
}

void BaseVisualizationTechnique::drawSetUp()
{
    initGl();
    initGlProgram();
    _isSetUp = _gl != nullptr && _program != nullptr;
}

void BaseVisualizationTechnique::draw(shared_ptr<Camera> camera)
{
    beforeDraw(camera);
    drawInternal(camera);
    afterDraw(camera);
}

void BaseVisualizationTechnique::initGl()
{
    _gl->glEnable(GL_DEPTH_TEST);
    _gl->glDepthFunc(GL_LEQUAL);
    _gl->glEnable(GL_CULL_FACE);
    _gl->glCullFace(GL_BACK);
    _gl->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    _gl->glClearColor(0, 0, 0, 0);
}

void BaseVisualizationTechnique::initGlProgram()
{
    _program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_BASIC_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_BASIC_FRAGMENT))
    );
}

void BaseVisualizationTechnique::beforeDraw(shared_ptr<Camera> camera)
{
}

void BaseVisualizationTechnique::drawInternal(shared_ptr<Camera> camera)
{
}

void BaseVisualizationTechnique::afterDraw(shared_ptr<Camera> camera)
{
}