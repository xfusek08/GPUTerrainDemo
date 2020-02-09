
#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <GeoPlanetDemo/core/Utils.h>
#include <GeoPlanetDemo/core/Camera.h>

#include <GeoPlanetDemo/vt/VAOContainer.h>
#include <GeoPlanetDemo/vt/PlanetVT.h>

using namespace std;
using namespace gpd;
using namespace gpd::vt;
using namespace gpd::entities;

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
	for (auto region : regions) {

        auto pos   = region->position.getGlobal();
        auto color = region->attributes[gp::RegionAttributeType::Color].data.uVector3;

		regionBuffer.push_back(pos.x);
		regionBuffer.push_back(pos.y);
		regionBuffer.push_back(pos.z);
        regionBuffer.push_back(0);
		regionBuffer.push_back(color.r / 255.0);
		regionBuffer.push_back(color.g / 255.0);
		regionBuffer.push_back(color.b / 255.0);
        regionBuffer.push_back(0);
	}

    auto vaoContainer = make_shared<VAOContainer>(_gl);
	_program->set1ui("resolution", _planet->meshResolution);
	_program->set1ui("showCube", _planet->showCube);

	_program->set1ui("regionResolution", _planet->getResolution());
	_program->bindBuffer("regionBuffer", vaoContainer->newBuffer(regionBuffer));

    GPD_LOG_DEBUG("resolution: " << _planet->meshResolution);
    GPD_LOG_DEBUG("regionResolution: " << _planet->getResolution());
    GPD_LOG_DEBUG("regionBufferSize: " << regionBuffer.size());
    return vaoContainer;
}

void PlanetVT::drawInternal(shared_ptr<core::Camera> camera)
{
    for (auto pair: _vaoContainerMap) {
		auto elem = pair.second;
		elem->vao->bind();
        _gl->glDrawArrays(GL_TRIANGLES, 0, 6 * 6 * _planet->meshResolution * _planet->meshResolution);
    }
}