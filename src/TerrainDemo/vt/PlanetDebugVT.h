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
        class PlanetDebugVT : public PlanetVT
        {
		public:
			PlanetDebugVT(std::shared_ptr<ge::gl::Context> gl) : PlanetVT(gl) {}

			inline VTType getType() const override { return VTType::PlanetDebugVT; }

		protected:
            std::shared_ptr<ge::gl::Program> _program_faces;
            std::shared_ptr<ge::gl::Program> _program_lines;

			virtual void initGlProgram() override;
			virtual void draw(std::shared_ptr<core::Camera> camera) override;
        };
    } // namespace vt
} // namespace TerrainDemo