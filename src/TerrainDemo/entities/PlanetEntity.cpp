
#include <TerrainDemo/entities/PlanetEntity.h>
#include <TerrainDemo/vt/VAOContainer.h>
#include <geGL/geGL.h>
#include <TerrainLib/PlanetSurface.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::entities;


PlanetEntity::PlanetEntity(vt::VTType vtType) : Entity(vtType)
{
	_surface = make_shared<tl::PlanetSurface>(_config);
}

void PlanetEntity::setRegionResolution(unsigned int value)
{
    if (value < 1) {
        value = 1;
    }
	_config.resolution = value;
	_surface->setConfig(_config);
}

void PlanetEntity::setJitter(float value)
{
    if (value < 0) {
        value = 0;
    } else if (value > 1) {
        value = 1;
    }

	_config.jitter = value;
	_surface->setConfig(_config);
}

void PlanetEntity::setShowFaceColor(bool value)
{
	_config.showFaceColor = value;
	_surface->setConfig(_config);
}
