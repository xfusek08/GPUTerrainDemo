
cmake_minimum_required(VERSION 3.12.4)

project(
    GPUTerrainProject-Demo
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

# find GPUTerrain library
if(NOT TARGET GPUTerrain)
    find_package(GPUTerrain REQUIRED)
endif()

if(NOT TARGET glm)
  find_package(glm REQUIRED)
endif()


set(DEFAULT_RESOERCES_PATH "${CMAKE_CURRENT_LIST_DIR}/resources")
set(${APP_NAME}_RESOURCES  "${DEFAULT_RESOERCES_PATH}" CACHE PATH "Relative or absolute path to Application resources.")

set(SRC_TERRAIN_DEMO
    src/${APP_NAME}/Application.h   src/${APP_NAME}/Application.cpp
    src/${APP_NAME}/TerrainDemoVT.h src/${APP_NAME}/TerrainDemoVT.cpp
    src/${APP_NAME}/TDScene.h
)

set(SRC_TERRAIN_DEMO_CORE
    src/${APP_NAME}/core/Log.h                      src/${APP_NAME}/core/Log.cpp
    src/${APP_NAME}/core/Camera.h                   src/${APP_NAME}/core/Camera.cpp
    src/${APP_NAME}/core/OrbitCameraController.h    src/${APP_NAME}/core/OrbitCameraController.cpp
    src/${APP_NAME}/core/Utils.h
)

set(SRC_ERRAIN_DEMO_TDSDL
    src/${APP_NAME}/tdsdl/SDLRenderer.h              src/${APP_NAME}/tdsdl/SDLRenderer.cpp
    src/${APP_NAME}/tdsdl/SDLOrbitCameraController.h src/${APP_NAME}/tdsdl/SDLOrbitCameraController.cpp
)

set(SRC_TERRAIN_DEMO_INTERFACES
    src/${APP_NAME}/interfaces/ILogger.h
    src/${APP_NAME}/interfaces/IScene.h
    src/${APP_NAME}/interfaces/ISDLEventReceiver.h
    src/${APP_NAME}/interfaces/IVisualizationTechnique.h
)

source_group("TerrainDemo" FILES ${SRC_TERRAIN_DEMO})
source_group("TerrainDemo\\core" FILES ${SRC_TERRAIN_DEMO_CORE})
source_group("TerrainDemo\\tdsdl" FILES ${SRC_ERRAIN_DEMO_TDSDL})
source_group("TerrainDemo\\interfaces" FILES ${SRC_TERRAIN_DEMO_INTERFACES})

# find shader files
find_file(vertexShader vertexShader.glsl
    HINTS ${${APP_NAME}_RESOURCES}/shaders
)

find_file(fragmentShader fragmentShader.glsl
    HINTS ${${APP_NAME}_RESOURCES}/shaders
)

add_executable(${APP_NAME}
    src/main.cpp
    ${SRC_TERRAIN_DEMO}
    ${SRC_TERRAIN_DEMO_CORE}
    ${SRC_ERRAIN_DEMO_TDSDL}
    ${SRC_TERRAIN_DEMO_INTERFACES}
)

target_link_libraries(${APP_NAME}
    geGL
    geUtil
    SDL2CPP::SDL2CPP
    GPUTerrain
    glm
)

target_include_directories(${APP_NAME}
    PRIVATE src
)

# add macra to code
target_compile_definitions(${APP_NAME} PUBLIC
    "VERTEX_SHADER=\"${vertexShader}\""
    "FRAGMENT_SHADER=\"${fragmentShader}\""
    $<$<CONFIG:DEBUG>: "GT_DEBUG" "GPTR_ENABLE_ASSERTS" >
)

message("VERTEX_SHADER=\"${vertexShader}\"")
message("FRAGMENT_SHADER=\"${fragmentShader}\"")

if(WIN32)
    set(LIBS_DLLS geCore geGL geUtil )
endif()
