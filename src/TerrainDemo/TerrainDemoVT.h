#pragma once

#include <TerrainDemo/Interfaces/IVisualizationTechnique.h>
#include <TerrainDemo/Interfaces/IScene.h>
#include <TerrainDemo/TDScene.h>

#include <memory>

namespace TerrainDemo
{
    class TerrainDemoVT : public Interfaces::IVisualizationTechnique
    {
    public:
        TerrainDemoVT();
        void draw() const override;
        void drawSetUp() override;
        void setScene(std::shared_ptr<Interfaces::IScene> scene) override;

    protected:
        std::shared_ptr<TDScene> _scene = nullptr;

        std::shared_ptr<ge::gl::Buffer> positions;
        std::shared_ptr<ge::gl::Buffer> colors;
        std::shared_ptr<ge::gl::Buffer> elementBuffer;
        std::shared_ptr<ge::gl::VertexArray> VAO;
    };

} // namespace TerrainDemo
