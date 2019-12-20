
#include <geGL/geGL.h>

#include <TerrainLib/PlanetSurface.h>

#include <TerrainDemo/entities/PlanetEntity.h>
#include <TerrainDemo/vt/VAOContainer.h>

#define STB_IMAGE_IMPLEMENTATION
#include <vendor/stb/stb_image.h>

using namespace std;
using namespace glm;
using namespace TerrainDemo;
using namespace TerrainDemo::entities;

PlanetEntity::PlanetEntity(vt::VTType vtType) : Entity(vtType)
{
	_surface = make_shared<tl::PlanetSurface>(_config);
}

void PlanetEntity::setRegionResolution(unsigned int value)
{
    if (value < 1) {
        value = 1;
    }
	_config.resolution = value;
	_surface->setConfig(_config);
}

void PlanetEntity::setJitter(float value)
{
    if (value < 0) {
        value = 0;
    } else if (value > 1) {
        value = 1;
    }

	_config.jitter = value;
	_surface->setConfig(_config);
}

void PlanetEntity::setShowFaceColor(bool value)
{
	_config.showFaceColor = value;
	_surface->setConfig(_config);
}

unique_ptr<unsigned char[]> PlanetEntity::getTextureDataForFace(unsigned int faceId, unsigned int face_width, unsigned int face_height) const
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load(COORDS_CUBE_MAP, &width, &height, &nrChannels, 0);

	uvec2 texOffset = uvec2(0, 0);
	switch (faceId) {
	 	case 0: texOffset = uvec2((width / 4) * 2, height / 3); break;
	 	case 1: texOffset = uvec2(0, height / 3); break;
	 	case 2: texOffset = uvec2(width / 4, 0); break;
	 	case 3: texOffset = uvec2(width / 4, height / 3 * 2); break;
		case 4: texOffset = uvec2(width / 4, height / 3); break;
		case 5: texOffset = uvec2(width / 4 * 3, height / 3); break;
	}

    auto tex = make_unique<unsigned char[]>(face_width * face_height * 4);
    for (unsigned int y = 0; y < face_height; ++y) {
		for (unsigned int x = 0; x < face_width;  ++x) {

			vec2 localWarpCoords = vec2(x / (float)face_width, y / (float)face_height);

            if (warpTexture) { // use warp method of coordinate system from tl
                localWarpCoords = (localWarpCoords - vec2(0.5, 0.5)) * 2.0f;
                localWarpCoords = glm::atan(localWarpCoords * 1.18228668555f) * 1.151099238f;
                localWarpCoords = localWarpCoords / 2.0f + vec2(0.5, 0.5);
            }

			uvec2 coords = uvec2(
				texOffset.x + (width / 4) * localWarpCoords.x,
				texOffset.y + (height / 3) * localWarpCoords.y
			);

			unsigned int i = (4 * x) + (4 * face_width * y);
			unsigned int j = (nrChannels * coords.x) + (nrChannels * coords.y * width);

			tex[i + 0] = data[j + 0];
			tex[i + 1] = data[j + 1];
			tex[i + 2] = data[j + 2];
			tex[i + 3] = data[j + 3];
        }
    }

	stbi_image_free(data);
    return tex;
}
