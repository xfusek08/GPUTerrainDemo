
cmake_minimum_required(VERSION 3.12.4)

project(
    TerrainLibProject-Demo
    VERSION 0.0.0
)

set(APP_NAME "TerrainDemo")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# find GPUengine library
if(NOT TARGET GPUEngine)
    find_package(GPUEngine COMPONENTS REQUIRED
        geCore
        geGL
        geUtil
    )
endif()

# find SDL2CPP library
if(NOT TARGET SDL2CPP)
    find_package(SDL2CPP REQUIRED)
endif()

# find TerrainLib library
if(NOT TARGET TerrainLib)
    find_package(TerrainLib REQUIRED)
endif()

if(NOT TARGET glm)
  find_package(glm REQUIRED)
endif()

# resources

set(DEFAULT_RESOERCES_PATH "${CMAKE_CURRENT_LIST_DIR}/resources")
set(${APP_NAME}_RESOURCES  "${DEFAULT_RESOERCES_PATH}" CACHE PATH "Relative or absolute path to Application resources.")

set(SHADER_FILES
    basic/vertex.glsl       basic/fragment.glsl
    vert_color/vertex.glsl  vert_color/fragment.glsl
    planet/vertex.glsl      planet/fragment.glsl        planet/fragment_lines.glsl  planet/fragment_cube_map.glsl
)

# source files

set(SRC_TERRAIN_DEMO
    src/${APP_NAME}/Application.h                     src/${APP_NAME}/Application.cpp
    src/${APP_NAME}/ApplicationEventReciever.h        src/${APP_NAME}/ApplicationEventReciever.cpp
)

set(SRC_TERRAIN_DEMO_CORE
    src/${APP_NAME}/core/Log.h                        src/${APP_NAME}/core/Log.cpp
    src/${APP_NAME}/core/Camera.h                     src/${APP_NAME}/core/Camera.cpp
    src/${APP_NAME}/core/OrbitCameraController.h      src/${APP_NAME}/core/OrbitCameraController.cpp
    src/${APP_NAME}/core/SceneRenderer.h              src/${APP_NAME}/core/SceneRenderer.cpp
    src/${APP_NAME}/core/Scene.h                      src/${APP_NAME}/core/Scene.cpp
    src/${APP_NAME}/core/Utils.h
)

set(SRC_TERRAIN_DEMO_ENTITIES
    src/${APP_NAME}/entities/Entity.h                 src/${APP_NAME}/entities/Entity.cpp
    src/${APP_NAME}/entities/AxisEntity.h             src/${APP_NAME}/entities/AxisEntity.cpp
    src/${APP_NAME}/entities/PlanetEntity.h           src/${APP_NAME}/entities/PlanetEntity.cpp
    src/${APP_NAME}/entities/PlanetCubeMapEntity.h    src/${APP_NAME}/entities/PlanetCubeMapEntity.cpp
)

set(SRC_ERRAIN_DEMO_TDSDL
    src/${APP_NAME}/tdsdl/SDLGlMainLoop.h             src/${APP_NAME}/tdsdl/SDLGlMainLoop.cpp
    src/${APP_NAME}/tdsdl/SDLOrbitCameraController.h  src/${APP_NAME}/tdsdl/SDLOrbitCameraController.cpp
    src/${APP_NAME}/tdsdl/SDLPerformance.h            src/${APP_NAME}/tdsdl/SDLPerformance.cpp
    src/${APP_NAME}/tdsdl/SDLEventReceiverInterface.h
)

set(SRC_ERRAIN_DEMO_VT
    src/${APP_NAME}/vt/types.h
    src/${APP_NAME}/vt/VTFactory.h
    src/${APP_NAME}/vt/VAOContainer.h                 src/${APP_NAME}/vt/VAOContainer.cpp
    src/${APP_NAME}/vt/BaseVisualizationTechnique.h   src/${APP_NAME}/vt/BaseVisualizationTechnique.cpp
    src/${APP_NAME}/vt/ColorLinesVT.h                 src/${APP_NAME}/vt/ColorLinesVT.cpp
    src/${APP_NAME}/vt/PlanetVT.h                     src/${APP_NAME}/vt/PlanetVT.cpp
    src/${APP_NAME}/vt/PlanetCubeMapVT.h              src/${APP_NAME}/vt/PlanetCubeMapVT.cpp
    src/${APP_NAME}/vt/PlanetDebugVT.h                src/${APP_NAME}/vt/PlanetDebugVT.cpp
)

set(SRC_TERRAIN_DEMO_INTERFACES
    src/${APP_NAME}/interfaces/LoggerInterface.h
    src/${APP_NAME}/interfaces/MainLoopInterface.h
    src/${APP_NAME}/interfaces/RendererInterface.h
)

set(SRC_VENDOR_STB
    src/vendor/stb/stb_image.h
)

source_group("TerrainDemo"              FILES ${SRC_TERRAIN_DEMO})
source_group("TerrainDemo\\core"        FILES ${SRC_TERRAIN_DEMO_CORE})
source_group("TerrainDemo\\entities"    FILES ${SRC_TERRAIN_DEMO_ENTITIES})
source_group("TerrainDemo\\vt"          FILES ${SRC_ERRAIN_DEMO_VT})
source_group("TerrainDemo\\tdsdl"       FILES ${SRC_ERRAIN_DEMO_TDSDL})
source_group("TerrainDemo\\interfaces"  FILES ${SRC_TERRAIN_DEMO_INTERFACES})

source_group("vendor/stb"               FILES ${SRC_VENDOR_STB} )

# generate shader definitions from SHADER_FILES based on their location
set(SHADER_COMPILE_DEFINITIONS )
foreach(FILE_RELATIVE_NAME ${SHADER_FILES})

   unset(shader_file CACHE)

    # find full name of shader
    find_file(shader_file
        ${FILE_RELATIVE_NAME}
        HINTS ${${APP_NAME}_RESOURCES}/shaders
    )

    # create shader definition string
    string(REPLACE "/" "_" definition_name ${FILE_RELATIVE_NAME})
    string(REPLACE "\\" "_" definition_name ${definition_name})
    string(REGEX REPLACE "\\..*" "" definition_name ${definition_name})
    string(TOUPPER ${definition_name} definition_name)
    string(CONCAT shader_definition
        "SHADER_" ${definition_name} "=\"" ${shader_file} "\""
    )

    messagE(${shader_definition})

    # add shader_definition to SHADER_COMPILE_DEFINITIONS list
    list(APPEND SHADER_COMPILE_DEFINITIONS ${shader_definition})
endforeach()

add_executable(${APP_NAME}
    src/main.cpp
    ${SRC_TERRAIN_DEMO}
    ${SRC_TERRAIN_DEMO_CORE}
    ${SRC_TERRAIN_DEMO_ENTITIES}
    ${SRC_ERRAIN_DEMO_VT}
    ${SRC_ERRAIN_DEMO_TDSDL}
    ${SRC_TERRAIN_DEMO_INTERFACES}
    ${SRC_VENDOR_STB}
)

target_link_libraries(${APP_NAME}
    geGL
    geUtil
    SDL2CPP::SDL2CPP
    TerrainLib::TerrainLib
    glm
)

target_include_directories(${APP_NAME}
    PRIVATE src
)

# texture files
find_file(textureImage
    coords_cube_map.png
    HINTS ${${APP_NAME}_RESOURCES/textures}
)

# add macra definitions to code
target_compile_definitions(${APP_NAME} PUBLIC
    ${SHADER_COMPILE_DEFINITIONS}
    $<$<CONFIG:DEBUG>: "TD_DEBUG" "TD_ENABLE_ASSERTS" >
    "COORDS_CUBE_MAP=\"${textureImage}\""
)
