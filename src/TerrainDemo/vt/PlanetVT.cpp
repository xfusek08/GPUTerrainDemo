
#include <TerrainDemo/core/Utils.h>
#include <TerrainDemo/core/Camera.h>

#include <TerrainDemo/vt/VAOContainer.h>
#include <TerrainDemo/vt/PlanetVT.h>
#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <TerrainLib/SurfaceConfig.h>
#include <TerrainLib/PlanetSurface.h>
#include <TerrainLib/SurfaceRegion.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::vt;

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

shared_ptr<VAOContainer> PlanetVT::processEntityToVaoContainer(std::shared_ptr<entities::Entity> entity)
{
	tl::SurfaceConfig config;
	config.resolution = 15;
	auto planetSurface = make_shared<tl::PlanetSurface>(config);
	auto regions = planetSurface->getRegions();
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
	_program->set1ui("resolution", 10);
	_program->set1ui("regionResolution", config.resolution);
	_program->bindBuffer("regionBuffer", vaoContainer->newBuffer(regionBuffer));
    return vaoContainer;
}

void PlanetVT::drawInternal(shared_ptr<core::Camera> camera)
{
    for (auto pair: _vaoContainerMap) {
		auto elem = pair.second;
		elem->vao->bind();
        _gl->glDrawArrays(GL_TRIANGLES, 0, 6 * 6 * 10 * 10);
    }
}