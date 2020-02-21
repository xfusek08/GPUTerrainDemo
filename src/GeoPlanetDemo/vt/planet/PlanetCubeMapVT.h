#pragma once

#include <GeoPlanetDemo/vt/planet/PlanetVT.h>

namespace ge
{
    namespace gl
    {
        class Texture;
    }
}

namespace gpd
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
            // methods
            PlanetCubeMapVT(VTType type, std::shared_ptr<ge::gl::Context> gl) : PlanetVT(type, gl) {}

        protected:
            // propertires
            std::shared_ptr<ge::gl::Texture> textureWarped;
            std::shared_ptr<ge::gl::Texture> texture;

            // methods
            virtual void initGlProgram() override;
            virtual std::shared_ptr<VAOContainer> processEntityToVaoContainer(std::shared_ptr<entities::Entity> entity) override;

            std::shared_ptr<ge::gl::Texture> loadTextureFromPlanet();
        };
    } // namespace vt
} // namespace gpd

REGISTER_VT_TYPE(PlanetCubeMapVT)
