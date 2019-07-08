#pragma once

#include <TerrainDemo/Interfaces/IControls.h>
#include <memory>

namespace TerrainDemo
{
    class TDCamera
    {
    public:
        void setControls(std::shared_ptr<Interfaces::IControls> controls);
    };
} // namespace TerrainDemo
