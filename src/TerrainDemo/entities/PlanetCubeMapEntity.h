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
            std::unique_ptr<unsigned char[]> getTextureDataForFace(unsigned int faceId, unsigned int face_width, unsigned int face_height);
        };
    } // namespace entities
} // namespace TerrainDemo
