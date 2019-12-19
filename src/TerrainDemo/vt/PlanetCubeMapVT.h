#pragma once

#include <TerrainDemo/vt/PlanetVT.h>

namespace TerrainDemo
{
    namespace core
	{
		class Camera;
    }

    namespace vt
    {
        class PlanetCubeMapVT : public PlanetVT
        {
		public:
			PlanetCubeMapVT(std::shared_ptr<ge::gl::Context> gl) : PlanetVT(gl) {}

			inline VTType getType() const override { return VTType::PlanetCubeMapVT; }
		protected:
			virtual void initGlProgram() override;
            virtual std::shared_ptr<VAOContainer> processEntityToVaoContainer(std::shared_ptr<entities::Entity> entity) override;
        };
    } // namespace vt
} // namespace TerrainDemo