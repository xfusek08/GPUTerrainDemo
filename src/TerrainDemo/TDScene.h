#pragma once

#include <memory>
#include <TerrainDemo/TDCamera.h>
#include <TerrainDemo/Interfaces/IScene.h>
#include <geGL/geGL.h>

namespace TerrainDemo
{
    class TDScene : public Interfaces::IScene
    {
    public:
        inline TDScene() : _camera(new TDCamera()) {}
        inline std::shared_ptr<TDCamera> getCamera() { return _camera; }

    protected:
        std::shared_ptr<TDCamera> _camera = nullptr;
    };
} // namespace TerrainDemo
