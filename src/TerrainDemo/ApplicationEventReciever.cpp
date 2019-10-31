
#include <TerrainDemo/ApplicationEventReciever.h>
#include <TerrainDemo/core/Scene.h>
#include <TerrainDemo/core/Utils.h>
#include <TerrainDemo/vt/types.h>
#include <TerrainDemo/entities/PlanetEntity.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::entities;

bool ApplicationEventReciever::processSDLEvent(SDL_Event const& event)
{
    switch(event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_F1) {
				auto planetEntity = _application->scene->getEntity("planet");
				if (planetEntity->getVtType() == vt::VTType::PlanetVT) {
					planetEntity->setVtType(vt::VTType::PlanetDebugVT);
				} else {
					planetEntity->setVtType(vt::VTType::PlanetVT);
				}
				_application->renderer->updateScene();
				return true;
			} else if (event.key.keysym.sym == SDLK_p) {
				auto planetEntity = dynamic_pointer_cast<PlanetEntity>(_application->scene->getEntity("planet"));
				planetEntity->setRegionResolution(planetEntity->getRegionResolution() + 1);
				_application->renderer->updateScene();
				return true;
			} else if (event.key.keysym.sym == SDLK_o) {
				auto planetEntity = dynamic_pointer_cast<PlanetEntity>(_application->scene->getEntity("planet"));
				planetEntity->setRegionResolution(planetEntity->getRegionResolution() - 1);
				_application->renderer->updateScene();
				return true;
			}
			else if (event.key.keysym.sym == SDLK_k) {
				auto planetEntity = dynamic_pointer_cast<PlanetEntity>(_application->scene->getEntity("planet"));
				planetEntity->setJitter(planetEntity->getJitter() + 0.1f);
				_application->renderer->updateScene();
				return true;
			}
			else if (event.key.keysym.sym == SDLK_j) {
				auto planetEntity = dynamic_pointer_cast<PlanetEntity>(_application->scene->getEntity("planet"));
				planetEntity->setJitter(planetEntity->getJitter() - 0.1f);
				_application->renderer->updateScene();
				return true;
			}
			else if (event.key.keysym.sym == SDLK_f) {
				auto planetEntity = dynamic_pointer_cast<PlanetEntity>(_application->scene->getEntity("planet"));
				planetEntity->setShowFaceColor(!planetEntity->getShowFaceColor());
				_application->renderer->updateScene();
				return true;
			}
			break;
    }
    return false;
}

void ApplicationEventReciever::onFrameUpdate()
{

}
