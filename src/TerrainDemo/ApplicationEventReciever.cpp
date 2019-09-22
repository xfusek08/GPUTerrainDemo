
#include <TerrainDemo/ApplicationEventReciever.h>
#include <TerrainDemo/core/Scene.h>
#include <TerrainDemo/core/Utils.h>
#include <TerrainDemo/vt/types.h>

using namespace TerrainDemo;

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
			}
			break;
    }
    return false;
}

void ApplicationEventReciever::onFrameUpdate()
{

}
