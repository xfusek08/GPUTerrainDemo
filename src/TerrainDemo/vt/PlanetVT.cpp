
#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <TerrainDemo/core/Utils.h>
#include <TerrainDemo/core/Camera.h>

#include <TerrainDemo/vt/VAOContainer.h>
#include <TerrainDemo/vt/PlanetVT.h>

#include <TerrainLib/SurfaceRegion.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::vt;
using namespace TerrainDemo::entities;

void PlanetVT::initGlProgram()
{
    _program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_PLANET_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_PLANET_FRAGMENT))
    );
}

void PlanetVT::processScene(std::shared_ptr<core::Scene> scene)
{
	BaseVisualizationTechnique::processScene(scene);
}

shared_ptr<VAOContainer> PlanetVT::processEntityToVaoContainer(shared_ptr<Entity> entity)
{
	_planet = dynamic_pointer_cast<PlanetEntity>(entity);
	auto regions = _planet->getRegions();
	vector<float> regionBuffer = {};
	for (tl::SurfaceRegion region : regions) {
		regionBuffer.push_back(region.get3dPosition().x);
		regionBuffer.push_back(region.get3dPosition().y);
		regionBuffer.push_back(region.get3dPosition().z);
        regionBuffer.push_back(0);
		regionBuffer.push_back(float(region.getColor().r) / 255.0);
		regionBuffer.push_back(float(region.getColor().g) / 255.0);
		regionBuffer.push_back(float(region.getColor().b) / 255.0);
        regionBuffer.push_back(0);
	}

    auto vaoContainer = make_shared<VAOContainer>(_gl);
	_program->set1ui("resolution", _planet->getMeshResolution());
	_program->set1ui("regionResolution", _planet->getRegionResolution());
	_program->bindBuffer("regionBuffer", vaoContainer->newBuffer(regionBuffer));

    TD_LOG_DEBUG("resolution: " << _planet->getMeshResolution());
    TD_LOG_DEBUG("regionResolution: " << _planet->getRegionResolution());
    TD_LOG_DEBUG("regionBufferSize: " << regionBuffer.size());
    return vaoContainer;
}

void PlanetVT::drawInternal(shared_ptr<core::Camera> camera)
{
    for (auto pair: _vaoContainerMap) {
		auto elem = pair.second;
		elem->vao->bind();
        _gl->glDrawArrays(GL_TRIANGLES, 0, 6 * 6 * _planet->getMeshResolution() * _planet->getMeshResolution());
    }
}