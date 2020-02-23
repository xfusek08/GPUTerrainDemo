#pragma once

#include <GeoPlanetDemo/entities/Entity.h>

#include <GeoPlanetLib/Surface.h>
#include <GeoPlanetLib/SurfaceGenerator.h>

namespace gpd
{
    namespace entities
    {
        class PlanetEntity : public Entity
        {
        public:
            // properties
            bool showCube = false;
            bool doWarp = true;
            bool showRegionBounds = false;
            unsigned int meshResolution = 10;

            // methods
            PlanetEntity(vt::VTType vtType);

            virtual std::vector<float>    getVerticies() const override { return {}; }
            virtual std::vector<unsigned> getIndieces()  const override { return {}; }
            virtual std::vector<float>    getColors()    const override { return {}; }

            inline unsigned int   getResolution()     const { return surface->getResolution(); }
            unsigned int          getNumberOfPlates() const;
            bool                  getShowFaceColor()  const;
            bool                  getStepPlates()     const;
            float                 getJitter()         const;
            const gp::RegionList& getRegions()        const { return surface->getRegions(); }

            void setResolution(unsigned int value);
            void setNumberOfPlates(unsigned int value);
            void setJitter(float value);
            void setStepPlates(bool value);

            void stepPlateExpansion();

            std::unique_ptr<unsigned char[]> getTextureDataForFace(unsigned int faceId, unsigned int face_width, unsigned int face_height) const;

        private:
            // properties
            std::shared_ptr<gp::SurfaceGenerator> generator;
            std::shared_ptr<gp::Surface> surface;

            // methods
            void generateFresh(unsigned int value = 0);
        };

    } // namespace entities
} // namespace gpd
