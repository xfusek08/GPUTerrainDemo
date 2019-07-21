#pragma once

#include <memory>

#include <geGL/geGL.h>

#include <TerrainDemo/interfaces/IVisualizationTechnique.h>
#include <TerrainDemo/core/Camera.h>
#include <TerrainDemo/core/Scene.h>
#include <TerrainDemo/TerrainScene.h>

namespace TerrainDemo
{
    class TerrainVT : public interfaces::IVisualizationTechnique
    {
    public:
        TerrainVT();
        void draw() override;
        void drawSetUp() override;
        void setScene(std::shared_ptr<core::Scene> scene) override;
        inline void setCamera(std::shared_ptr<core::Camera> camera) { _camera = camera; }

    protected:
        std::shared_ptr<TerrainScene> _scene = nullptr;
        std::shared_ptr<core::Camera> _camera = nullptr;

        // BEGIN temporal test delete when proper model/terrain is loaded -------------------------------
        std::shared_ptr<ge::gl::Buffer> positions;
        std::shared_ptr<ge::gl::Buffer> colors;
        std::shared_ptr<ge::gl::Buffer> elementBuffer;
        std::shared_ptr<ge::gl::VertexArray> VAO;
        // END temporal test delete when proper model/terrain is loaded -------------------------------
    };

} // namespace TerrainDemo
