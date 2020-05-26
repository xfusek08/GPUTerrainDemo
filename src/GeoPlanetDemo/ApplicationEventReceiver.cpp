
#include <GeoPlanetDemo/ApplicationEventReceiver.h>
#include <GeoPlanetDemo/core/Camera.h>
#include <GeoPlanetDemo/core/Utils.h>
#include <GeoPlanetDemo/vt/planet/vts.h>
#include <GeoPlanetDemo/scene/Scene.h>
#include <GeoPlanetDemo/scene/entities/PlanetEntity.h>

using namespace std;
using namespace gpd;
using namespace gpd::scene::entities;

#define RUN_FOR_ELEMENT(_ident, _code) {\
    auto element = application->scene->getElement(_ident);\
    _code\
}\
return false

#define RUN_FOR_PLANET(_code)\
    RUN_FOR_ELEMENT("planet", {\
        auto planetEntity = dynamic_pointer_cast<PlanetEntity>(element.entity);\
        if (planetEntity != nullptr) {\
            bool updateScene = true;\
            {_code}\
            if (updateScene) {\
                application->renderer->updateScene();\
            }\
            return true;\
        }\
    })

#define RUN_SET_ELEMENT_VT(elem, vt)\
    RUN_FOR_ELEMENT(elem, {\
        if (element.vtType != vt) {\
            element.vtType = vt;\
            application->scene->setElement(elem, element);\
            application->renderer->updateScene();\
            application->camera->setViewChanged();\
        }\
        return true;\
    })

bool ApplicationEventReceiver::processSDLEvent(SDL_Event const& event)
{
    switch(event.type) {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
                case SDLK_F1: RUN_SET_ELEMENT_VT("planet", vt::types::PlanetElevationVT);
                case SDLK_F2: RUN_SET_ELEMENT_VT("planet", vt::types::PlanetPlatesVT);
                case SDLK_F3: RUN_SET_ELEMENT_VT("planet", vt::types::PlanetFaceColorVT);
                case SDLK_F4: RUN_SET_ELEMENT_VT("planet", vt::types::PlanetWireFrameVT);
                // case SDLK_F5: RUN_SET_ELEMENT_VT("planet", vt::types::PlanetCubeMapVT);

                case SDLK_p: RUN_FOR_PLANET({
                    planetEntity->setResolution(planetEntity->getResolution() + 1);
                });

                case SDLK_o: RUN_FOR_PLANET({
                    planetEntity->setResolution(planetEntity->getResolution() - 1);
                });

                case SDLK_c: RUN_FOR_PLANET({
                    planetEntity->showCube = !planetEntity->showCube;
                });

                case SDLK_l: RUN_FOR_PLANET({
                    updateScene = planetEntity->setJitter(planetEntity->getJitter() + 0.1f);
                });

                case SDLK_k: RUN_FOR_PLANET({
                    updateScene = planetEntity->setJitter(planetEntity->getJitter() - 0.1f);
                });

                case SDLK_b: RUN_FOR_PLANET({
                    planetEntity->showRegionBounds = !planetEntity->showRegionBounds;
                });

                case SDLK_v: RUN_FOR_PLANET({
                    planetEntity->doWarp = !planetEntity->doWarp;
                });

                case SDLK_g: RUN_FOR_PLANET({
                    planetEntity->generateFresh(planetEntity->getResolution());
                });
            }
            break;
        default: break;
    }
    return false;
}

void ApplicationEventReceiver::onFrameUpdate()
{
}
