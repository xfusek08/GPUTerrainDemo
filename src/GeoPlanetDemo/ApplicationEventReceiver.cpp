
#include <GeoPlanetDemo/ApplicationEventReceiver.h>
#include <GeoPlanetDemo/core/Scene.h>
#include <GeoPlanetDemo/core/Camera.h>
#include <GeoPlanetDemo/core/Utils.h>
#include <GeoPlanetDemo/vt/planet/vts.h>
#include <GeoPlanetDemo/entities/PlanetEntity.h>

using namespace std;
using namespace gpd;
using namespace gpd::entities;

// TODO: use anonymous function
#define RUN_FOR_PLANET(code) {\
        auto planetEntity = dynamic_pointer_cast<PlanetEntity>(application->scene->getEntity("planet"));\
        if (planetEntity != nullptr) {\
            code\
            return true;\
        }\
    }\
    return false

bool ApplicationEventReceiver::processSDLEvent(SDL_Event const& event)
{
    switch(event.type) {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
                case SDLK_F1: RUN_FOR_PLANET({
                    if (planetEntity->setVtType(vt::types::PlanetElevationVT)) {
                        application->renderer->updateScene();
                        application->camera->setViewChanged();
                    }
                });

                case SDLK_F2: RUN_FOR_PLANET({
                    if (planetEntity->setVtType(vt::types::PlanetPlatesVT)) {
                        application->renderer->updateScene();
                        application->camera->setViewChanged();
                    }
                });

                case SDLK_F3: RUN_FOR_PLANET({
                    if (planetEntity->setVtType(vt::types::PlanetCubeMapVT)) {
                        application->renderer->updateScene();
                        application->camera->setViewChanged();
                    }
                });

                case SDLK_F4: RUN_FOR_PLANET({
                    if (planetEntity->setVtType(vt::types::PlanetFaceColorVT)) {
                        application->renderer->updateScene();
                        application->camera->setViewChanged();
                    }
                });

                case SDLK_p: RUN_FOR_PLANET({
                    planetEntity->setResolution(planetEntity->getResolution() + 1);
                    application->renderer->updateScene();
                });

                case SDLK_o: RUN_FOR_PLANET({
                    planetEntity->setResolution(planetEntity->getResolution() - 1);
                    application->renderer->updateScene();
                });

                case SDLK_l: RUN_FOR_PLANET({
                    planetEntity->setJitter(planetEntity->getJitter() + 0.1f);
                    application->renderer->updateScene();
                });

                case SDLK_k: RUN_FOR_PLANET({
                    planetEntity->setJitter(planetEntity->getJitter() - 0.1f);
                    application->renderer->updateScene();
                });

                case SDLK_m: RUN_FOR_PLANET({
                    planetEntity->setNumberOfPlates(planetEntity->getNumberOfPlates() + 1);
                    application->renderer->updateScene();
                });

                case SDLK_n: RUN_FOR_PLANET({
                    planetEntity->setNumberOfPlates(planetEntity->getNumberOfPlates() - 1);
                    application->renderer->updateScene();
                });

                case SDLK_c: RUN_FOR_PLANET({
                    planetEntity->showCube = !planetEntity->showCube;
                    application->renderer->updateScene();
                });

                case SDLK_b: RUN_FOR_PLANET({
                    planetEntity->showRegionBounds = !planetEntity->showRegionBounds;
                    application->renderer->updateScene();
                });

                case SDLK_v: RUN_FOR_PLANET({
                    planetEntity->doWarp = !planetEntity->doWarp;
                    application->renderer->updateScene();
                });
            }
        default: break;
    }
    return false;
}

void ApplicationEventReceiver::onFrameUpdate()
{
}
