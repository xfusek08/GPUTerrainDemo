
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

set(DEFAULT_RESOERCES_PATH "${CMAKE_CURRENT_LIST_DIR}/resources")
set(${APP_NAME}_RESOURCES  "${DEFAULT_RESOERCES_PATH}" CACHE PATH "Relative or absolute path to Application resources.")

set(TERRAIN_DEMO_HEADERS
    src/${APP_NAME}/Application.h
    src/${APP_NAME}/Log.h
    src/${APP_NAME}/BasicLogger.h
    src/${APP_NAME}/SDLRenderer.h
    src/${APP_NAME}/utils.h
)

set(TERRAIN_DEMO_SOURCES
    src/${APP_NAME}/Application.cpp
    src/${APP_NAME}/Log.cpp
    src/${APP_NAME}/SDLRenderer.cpp
)

set(TERRAIN_DEMO_INTERFACES
    src/${APP_NAME}/Interfaces/ILogger.h
)

source_group("Interfaces" FILES ${TERRAIN_DEMO_INTERFACES})

# message(${TERRAIN_DEMO_HEADERS})
# message(${TERRAIN_DEMO_SOURCES})
# message(${TERRAIN_DEMO_INTERFACES})

# find shader files
find_file(vertexShader vertexShader.glsl
    HINTS ${${APP_NAME}_RESOURCES}/shaders
)

find_file(fragmentShader fragmentShader.glsl
    HINTS ${${APP_NAME}_RESOURCES}/shaders
)

add_executable(${APP_NAME}
    src/main.cpp
    ${TERRAIN_DEMO_HEADERS}
    ${TERRAIN_DEMO_SOURCES}
    ${TERRAIN_DEMO_INTERFACES}
)

target_link_libraries(${APP_NAME}
    geGL
    geUtil
    SDL2CPP::SDL2CPP
    GPUTerrain
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

if(WIN32)
    set(LIBS_DLLS geCore geGL geUtil )
endif()
