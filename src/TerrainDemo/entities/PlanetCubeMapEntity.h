#pragma once

#include <TerrainDemo/entities/PlanetEntity.h>

namespace TerrainDemo
{
    namespace entities
    {
        class PlanetCubeMapEntity : public PlanetEntity
        {
        public:
			PlanetCubeMapEntity(vt::VTType vtType) : PlanetEntity(vtType) {}
        };
    } // namespace entities
} // namespace TerrainDemo
