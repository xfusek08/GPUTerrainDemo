#pragma once

#include <GeoPlanetDemo/entities/Entity.h>

#include <GeoPlanetLib/Surface.h>
#include <GeoPlanetLib/SurfaceGenerator.h>
#include <GeoPlanetLib/Region.h>

namespace gpd
{
    namespace entities
    {
        class PlanetEntity : public entities::Entity
        {
		public:
    		// properties
            bool showCube = false;
            bool warpTexture = true;
            unsigned int meshResolution = 10;

    		// methods
			PlanetEntity(vt::VTType vtType);

            virtual std::vector<float>    getVerticies() const override { return {}; }
            virtual std::vector<unsigned> getIndieces()  const override { return {}; }
            virtual std::vector<float>    getColors()    const override { return {}; }

			inline unsigned int getResolution() const { return surface->getResolution(); }
            bool  getShowFaceColor() const;
			float getJitter() const;

			void setResolution(unsigned int value);
			void setJitter(float value);
            void setShowFaceColor(bool value);

			const gp::RegionList& getRegions() const { return surface->getRegions(); }

			std::unique_ptr<unsigned char[]> getTextureDataForFace(unsigned int faceId, unsigned int face_width, unsigned int face_height) const;

		private:
    		// properties
            std::shared_ptr<gp::SurfaceGenerator> generator;
			std::shared_ptr<gp::Surface> surface;

            // methods
            void refreshSurface();
        };

    } // namespace entities
} // namespace  gpd
