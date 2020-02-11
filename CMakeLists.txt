
cmake_minimum_required(VERSION 3.12.4)

project(
    GeoPlanetProject-Demo
    VERSION 0.0.0
)

set(APP_NAME "GeoPlanetDemo")

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

# find GeoPlanet library
if(NOT TARGET GeoPlanetLib)
    find_package(GeoPlanetLib REQUIRED)
endif()

if(NOT TARGET glm)
  find_package(glm REQUIRED)
endif()

# resources

set(DEFAULT_RESOERCES_PATH "${CMAKE_CURRENT_LIST_DIR}/resources")
set(${APP_NAME}_RESOURCES  "${DEFAULT_RESOERCES_PATH}" CACHE PATH "Relative or absolute path to Application resources.")

set(SHADER_FILES
    # vertex                # fragment
    basic/vertex.glsl       basic/fragment.glsl
    vert_color/vertex.glsl  vert_color/fragment.glsl
    planet/vertex.glsl      planet/fragment.glsl        planet/fragment_lines.glsl  planet/fragment_cube_map.glsl
)

# source files

set(SRC_GEO_PLANET_DEMO
    src/${APP_NAME}/Application.h                     src/${APP_NAME}/Application.cpp
    src/${APP_NAME}/ApplicationEventReceiver.h        src/${APP_NAME}/ApplicationEventReceiver.cpp
    src/${APP_NAME}/ApplicationGui.h                  src/${APP_NAME}/ApplicationGui.cpp
)

set(SRC_GEO_PLANET_DEMO_CORE
    src/${APP_NAME}/core/Log.h                        src/${APP_NAME}/core/Log.cpp
    src/${APP_NAME}/core/Camera.h                     src/${APP_NAME}/core/Camera.cpp
    src/${APP_NAME}/core/OrbitCameraController.h      src/${APP_NAME}/core/OrbitCameraController.cpp
    src/${APP_NAME}/core/SceneRenderer.h              src/${APP_NAME}/core/SceneRenderer.cpp
    src/${APP_NAME}/core/Scene.h                      src/${APP_NAME}/core/Scene.cpp
    src/${APP_NAME}/core/Utils.h
)

set(SRC_GEO_PLANET_DEMO_ENTITIES
    src/${APP_NAME}/entities/Entity.h                 src/${APP_NAME}/entities/Entity.cpp
    src/${APP_NAME}/entities/AxisEntity.h             src/${APP_NAME}/entities/AxisEntity.cpp
    src/${APP_NAME}/entities/PlanetEntity.h           src/${APP_NAME}/entities/PlanetEntity.cpp
)

set(SRC_GEO_PLANET_DEMO_SDL
    src/${APP_NAME}/sdl/SDLGlMainLoop.h               src/${APP_NAME}/SDL/SDLGlMainLoop.cpp
    src/${APP_NAME}/sdl/SDLOrbitCameraController.h    src/${APP_NAME}/sdl/SDLOrbitCameraController.cpp
    src/${APP_NAME}/sdl/SDLPerformance.h              src/${APP_NAME}/sdl/SDLPerformance.cpp
    src/${APP_NAME}/sdl/SDLEventReceiverInterface.h
)

set(SRC_GEO_PLANET_DEMO_VT
    src/${APP_NAME}/vt/types.h
    src/${APP_NAME}/vt/VTFactory.h
    src/${APP_NAME}/vt/VAOContainer.h                 src/${APP_NAME}/vt/VAOContainer.cpp
    src/${APP_NAME}/vt/BaseVisualizationTechnique.h   src/${APP_NAME}/vt/BaseVisualizationTechnique.cpp
    src/${APP_NAME}/vt/ColorLinesVT.h                 src/${APP_NAME}/vt/ColorLinesVT.cpp
    src/${APP_NAME}/vt/PlanetVT.h                     src/${APP_NAME}/vt/PlanetVT.cpp
    src/${APP_NAME}/vt/PlanetCubeMapVT.h              src/${APP_NAME}/vt/PlanetCubeMapVT.cpp
    src/${APP_NAME}/vt/PlanetDebugVT.h                src/${APP_NAME}/vt/PlanetDebugVT.cpp
)

set(SRC_GEO_PLANET_DEMO_INTERFACES
    src/${APP_NAME}/interfaces/LoggerInterface.h
    src/${APP_NAME}/interfaces/MainLoopInterface.h
    src/${APP_NAME}/interfaces/RendererInterface.h
)

set(SRC_VENDOR_STB
    src/vendor/stb/stb_image.h
)

set(SRC_VENDOR_IAMGUI
    src/vendor/imgui/imconfig.h
    src/vendor/imgui/imgui.cpp
    src/vendor/imgui/imgui.h
    # src/vendor/imgui/imgui_demo.cpp
    src/vendor/imgui/imgui_draw.cpp
    src/vendor/imgui/imgui_impl_opengl3.cpp
    src/vendor/imgui/imgui_impl_opengl3.h
    src/vendor/imgui/imgui_impl_sdl.cpp
    src/vendor/imgui/imgui_impl_sdl.h
    src/vendor/imgui/imgui_internal.h
    src/vendor/imgui/imgui_widgets.cpp
    src/vendor/imgui/imstb_rectpack.h
    src/vendor/imgui/imstb_textedit.h
    src/vendor/imgui/imstb_truetype.h
)

source_group("GeoPlanetDemo"             FILES ${SRC_GEO_PLANET_DEMO})
source_group("GeoPlanetDemo\\core"       FILES ${SRC_GEO_PLANET_DEMO_CORE})
source_group("GeoPlanetDemo\\entities"   FILES ${SRC_GEO_PLANET_DEMO_ENTITIES})
source_group("GeoPlanetDemo\\vt"         FILES ${SRC_GEO_PLANET_DEMO_VT})
source_group("GeoPlanetDemo\\sdl"        FILES ${SRC_GEO_PLANET_DEMO_SDL})
source_group("GeoPlanetDemo\\interfaces" FILES ${SRC_GEO_PLANET_DEMO_INTERFACES})

source_group("vendor/stb"                FILES ${SRC_VENDOR_STB})
source_group("vendor/imgui"              FILES ${SRC_VENDOR_IAMGUI})

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

    message(${shader_definition})

    # add shader_definition to SHADER_COMPILE_DEFINITIONS list
    list(APPEND SHADER_COMPILE_DEFINITIONS ${shader_definition})
endforeach()

add_executable(${APP_NAME}
    src/main.cpp
    ${SRC_GEO_PLANET_DEMO}
    ${SRC_GEO_PLANET_DEMO_CORE}
    ${SRC_GEO_PLANET_DEMO_ENTITIES}
    ${SRC_GEO_PLANET_DEMO_VT}
    ${SRC_GEO_PLANET_DEMO_SDL}
    ${SRC_GEO_PLANET_DEMO_INTERFACES}
    ${SRC_VENDOR_STB}
    ${SRC_VENDOR_IAMGUI}
)

target_link_libraries(${APP_NAME}
    geGL
    geUtil
    SDL2CPP::SDL2CPP
    GeoPlanetLib::GeoPlanetLib
    glm
)

target_include_directories(${APP_NAME}
    PRIVATE src
)

# texture files
find_file(coordCubeMapImage
    coords_cube_map.png
    HINTS ${${APP_NAME}_RESOURCES}/textures
)

message("COORDS_CUBE_MAP=\"${coordCubeMapImage}\"")

# add macra definitions to code
target_compile_definitions(${APP_NAME} PUBLIC
    ${SHADER_COMPILE_DEFINITIONS}
    $<$<CONFIG:DEBUG>: "GPD_DEBUG" "GPD_ENABLE_ASSERTS" >
    "COORDS_CUBE_MAP=\"${coordCubeMapImage}\""
)
