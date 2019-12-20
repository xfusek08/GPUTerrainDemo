#pragma once

#include <TerrainDemo/entities/Entity.h>

#include <TerrainLib/SurfaceConfig.h>
#include <TerrainLib/PlanetSurface.h>
#include <TerrainLib/SurfaceRegion.h>

namespace TerrainDemo
{
    namespace entities
    {
        class PlanetEntity : public entities::Entity
        {
		// properties
        public:
			unsigned int meshResolution = 10;
            bool showCube = false;
			bool warpTexture = true;

		private:
			tl::SurfaceConfig _config;
			std::shared_ptr<tl::PlanetSurface> _surface;

		// methods
		public:
			PlanetEntity(vt::VTType vtType);

			// virtual
            virtual std::vector<float>    getVerticies() const override { return {}; }
            virtual std::vector<unsigned> getIndieces()  const override { return {}; }
            virtual std::vector<float>    getColors()    const override { return {}; }

			// getters
			inline unsigned int getRegionResolution() const { return _config.resolution; }
			inline float	    getJitter()			  const { return _config.jitter; }
			inline bool			getShowFaceColor()    const { return _config.showFaceColor; }

			inline const std::vector<tl::SurfaceRegion>& getRegions() const { return _surface->getRegions(); }

			std::unique_ptr<unsigned char[]> getTextureDataForFace(unsigned int faceId, unsigned int face_width, unsigned int face_height) const;

			// setters
			void setRegionResolution(unsigned int value);
			void setJitter(float value);
			void setShowFaceColor(bool value);

        };
    } // namespace entities
} // namespace TerrainDemo
