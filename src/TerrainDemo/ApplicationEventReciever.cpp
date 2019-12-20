
#include <TerrainDemo/ApplicationEventReciever.h>
#include <TerrainDemo/core/Scene.h>
#include <TerrainDemo/core/Utils.h>
#include <TerrainDemo/vt/types.h>
#include <TerrainDemo/entities/PlanetEntity.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::entities;

// TODO: use anonymous function
#define RUN_FOR_PLANET(code) {\
	auto planetEntity = dynamic_pointer_cast<PlanetEntity>(_application->scene->getEntity("planet")); \
	if (planetEntity != nullptr) { \
		code \
		return true; \
	} \
} \
return false

bool ApplicationEventReciever::processSDLEvent(SDL_Event const& event)
{
    switch(event.type) {
		case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
                case SDLK_F1: RUN_FOR_PLANET({
					if (planetEntity->getVtType() != vt::VTType::PlanetVT) {
						planetEntity->setVtType(vt::VTType::PlanetVT);
                        _application->renderer->updateScene();
					}
				});

                case SDLK_F2: RUN_FOR_PLANET({
					if (planetEntity->getVtType() != vt::VTType::PlanetDebugVT) {
						planetEntity->setVtType(vt::VTType::PlanetDebugVT);
                        _application->renderer->updateScene();
					}
				});

                case SDLK_F3: RUN_FOR_PLANET({
					if (planetEntity->getVtType() != vt::VTType::PlanetCubeMapVT) {
						planetEntity->setVtType(vt::VTType::PlanetCubeMapVT);
                        _application->renderer->updateScene();
					}
				});

                case SDLK_p: RUN_FOR_PLANET({
					planetEntity->setRegionResolution(planetEntity->getRegionResolution() + 1);
					_application->renderer->updateScene();
				});

                case SDLK_o: RUN_FOR_PLANET({
                    planetEntity->setRegionResolution(planetEntity->getRegionResolution() - 1);
                    _application->renderer->updateScene();
				});

                case SDLK_k: RUN_FOR_PLANET({
                    planetEntity->setJitter(planetEntity->getJitter() + 0.1f);
                    _application->renderer->updateScene();
				});

                case SDLK_j: RUN_FOR_PLANET({
                    planetEntity->setJitter(planetEntity->getJitter() - 0.1f);
                    _application->renderer->updateScene();
				});

                case SDLK_f: RUN_FOR_PLANET({
                    planetEntity->setShowFaceColor(!planetEntity->getShowFaceColor());
                    _application->renderer->updateScene();
				});

                case SDLK_c: RUN_FOR_PLANET({
					planetEntity->showCube = !planetEntity->showCube;
					_application->renderer->updateScene();
				});

                case SDLK_v: RUN_FOR_PLANET({
					planetEntity->warpTexture = !planetEntity->warpTexture;
					_application->renderer->updateScene();
				});
            }
        default: break;
    }
    return false;
}

void ApplicationEventReciever::onFrameUpdate()
{

}
