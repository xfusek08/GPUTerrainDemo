#pragma once

#include <TerrainDemo/vt/PlanetVT.h>

namespace ge
{
	namespace gl
	{
		class Texture;
	}
}

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
		private: // propertires
			std::shared_ptr<ge::gl::Texture> _textureWarped = nullptr;
            std::shared_ptr<ge::gl::Texture> _texture = nullptr;

		public:// methods
			PlanetCubeMapVT(std::shared_ptr<ge::gl::Context> gl) : PlanetVT(gl) {}

			inline VTType getType() const override { return VTType::PlanetCubeMapVT; }

		protected: // methods
			virtual void initGlProgram() override;
            virtual std::shared_ptr<VAOContainer> processEntityToVaoContainer(std::shared_ptr<entities::Entity> entity) override;

		private: // methods
			std::shared_ptr<ge::gl::Texture> loadTextureFromPlanet();

        };
    } // namespace vt
} // namespace TerrainDemo