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
        public:
			PlanetEntity(vt::VTType vtType);

			// virtual
            virtual std::vector<float>    getVerticies() const override { return {}; }
            virtual std::vector<unsigned> getIndieces()  const override { return {}; }
            virtual std::vector<float>    getColors()    const override { return {}; }

			// getters
			inline unsigned int getMeshResolution()   const { return _meshResolution; }
			inline unsigned int getRegionResolution() const { return _config.resolution; }
			inline float	    getJitter()			  const { return _config.jitter; }
			inline bool			getShowFaceColor()    const { return _config.showFaceColor; }

			inline const std::vector<tl::SurfaceRegion>& getRegions() const { return _surface->getRegions(); }

			// setters
			void setRegionResolution(unsigned int value);
			void setJitter(float value);
			void setShowFaceColor(bool value);

		private:
			unsigned int _meshResolution = 10;
			tl::SurfaceConfig _config;
			std::shared_ptr<tl::PlanetSurface> _surface;
        };
    } // namespace entities
} // namespace TerrainDemo
