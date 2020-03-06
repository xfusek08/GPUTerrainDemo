#pragma once

#include <GeoPlanetDemo/vt/planet/PlanetVT.h>
#include <GeoPlanetDemo/scene/entities/PlanetEntity.h>

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

            virtual glm::uvec4 regionToColor(std::shared_ptr<gp::Region> region) override { return glm::uvec4(0); }

        protected:
            // propertires
            std::shared_ptr<ge::gl::Texture> textureWarped;
            std::shared_ptr<ge::gl::Texture> texture;

            // methods
            virtual void initGlProgram() override;
            virtual std::shared_ptr<VAOContainer> processEntityToVaoContainer(std::shared_ptr<scene::Entity> entity) override;

            std::shared_ptr<ge::gl::Texture> loadTextureFromPlanet(std::shared_ptr<scene::entities::PlanetEntity> planet);
        };
    } // namespace vt
} // namespace gpd

REGISTER_VT_TYPE(PlanetCubeMapVT)
