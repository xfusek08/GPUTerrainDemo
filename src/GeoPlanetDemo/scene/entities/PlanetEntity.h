#pragma once

#include <GeoPlanetDemo/scene/Entity.h>

#include <GeoPlanetLib/Surface.h>
#include <GeoPlanetLib/SurfaceGenerator.h>

namespace gpd
{
    namespace scene
    {
        namespace entities
        {
            class PlanetEntity : public Entity
            {
            public:
                // properties
                std::shared_ptr<gp::SurfaceGenerator> generator;
                std::shared_ptr<gp::Surface> surface;
                bool showCube = false;
                bool doWarp = true;
                bool showRegionBounds = false;
                unsigned int meshResolution = 10;

                // methods
                PlanetEntity();

                inline unsigned int                 getResolution() const { return surface->getResolution(); }
                inline std::shared_ptr<gp::Surface> getSurface()    const { return surface; }

                bool         getShowFaceColor()  const;
                bool         getStepPlates()     const;
                float        getJitter()         const;

                void setResolution(unsigned int value);
                void setStepPlates(bool value);
                bool setJitter(float value);

                void stepPlateExpansion();

                std::unique_ptr<unsigned char[]> getTextureDataForFace(unsigned int faceId, unsigned int face_width, unsigned int face_height) const;

                void generateFresh(unsigned int value = 0);
            };

        } // namespace entities
    } // namespace scene
} // namespace gpd
