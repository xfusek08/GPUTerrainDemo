
cmake_minimum_required(VERSION 3.15)

project(
    GeoPlanetDemo
    VERSION 0.0.0
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_DEBUG_POSTFIX          "d"  CACHE STRING "add a postfix, usually d on windows"    )
SET(CMAKE_RELEASE_POSTFIX        ""   CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX     "s"  CACHE STRING "add a postfix, usually empty on windows")

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
set(${PROJECT_NAME}_RESOURCES  "${DEFAULT_RESOERCES_PATH}" CACHE PATH "Relative or absolute path to Application resources.")

set(SHADER_FILES
    # vertex                          # fragment
    # demostartion triangle
    basic/vertex.glsl                 basic/fragment.glsl
    # color (axis)
    vert_color/vertex.glsl            vert_color/fragment.glsl
    # planet
    planet/calculateSphereVertex.glsl
    planet_vectors/vertex.glsl        planet_vectors/fragment.glsl
    planet/vertex.glsl                planet/fragment.glsl planet/fragment_lines.glsl  planet/fragment_cube_map.glsl
)

# source files
        # HEADERS #                                         # SOURCES #
set(SRC_GEO_PLANET_DEMO
    src/${PROJECT_NAME}/Application.h                     src/${PROJECT_NAME}/Application.cpp
    src/${PROJECT_NAME}/ApplicationEventReceiver.h        src/${PROJECT_NAME}/ApplicationEventReceiver.cpp
    src/${PROJECT_NAME}/ApplicationGui.h                  src/${PROJECT_NAME}/ApplicationGui.cpp
    src/${PROJECT_NAME}/ModifierPropertyWidowGui.h        src/${PROJECT_NAME}/ModifierPropertyWidowGui.cpp
)

set(SRC_GEO_PLANET_DEMO_CORE
    src/${PROJECT_NAME}/core/Utils.h
    src/${PROJECT_NAME}/core/Log.h                        src/${PROJECT_NAME}/core/Log.cpp
    src/${PROJECT_NAME}/core/Camera.h                     src/${PROJECT_NAME}/core/Camera.cpp
    src/${PROJECT_NAME}/core/OrbitCameraController.h      src/${PROJECT_NAME}/core/OrbitCameraController.cpp
    src/${PROJECT_NAME}/core/SceneRenderer.h              src/${PROJECT_NAME}/core/SceneRenderer.cpp
)

set(SRC_GEO_PLANET_DEMO_SCENE
    src/${PROJECT_NAME}/scene/Scene.h                     src/${PROJECT_NAME}/scene/Scene.cpp
    src/${PROJECT_NAME}/scene/Entity.h                    src/${PROJECT_NAME}/scene/Entity.cpp
)

set(SRC_GEO_PLANET_DEMO_SCENE_ENTITIES
    src/${PROJECT_NAME}/scene/entities/AxisEntity.h       src/${PROJECT_NAME}/scene/entities/AxisEntity.cpp
    src/${PROJECT_NAME}/scene/entities/PlanetEntity.h     src/${PROJECT_NAME}/scene/entities/PlanetEntity.cpp
)

set(SRC_GEO_PLANET_DEMO_SDL
    src/${PROJECT_NAME}/sdl/SDLEventReceiverInterface.h
    src/${PROJECT_NAME}/sdl/SDLGlMainLoop.h               src/${PROJECT_NAME}/SDL/SDLGlMainLoop.cpp
    src/${PROJECT_NAME}/sdl/SDLOrbitCameraController.h    src/${PROJECT_NAME}/sdl/SDLOrbitCameraController.cpp
    src/${PROJECT_NAME}/sdl/SDLPerformance.h              src/${PROJECT_NAME}/sdl/SDLPerformance.cpp
)

set(SRC_GEO_PLANET_DEMO_VT
    src/${PROJECT_NAME}/vt/VTType.h
    src/${PROJECT_NAME}/vt/VTFactory.h
    src/${PROJECT_NAME}/vt/VAOContainer.h                 src/${PROJECT_NAME}/vt/VAOContainer.cpp
    src/${PROJECT_NAME}/vt/VisualizationTechnique.h       src/${PROJECT_NAME}/vt/VisualizationTechnique.cpp
    src/${PROJECT_NAME}/vt/ColorLinesVT.h                 src/${PROJECT_NAME}/vt/ColorLinesVT.cpp
)

set(SRC_GEO_PLANET_DEMO_VT_PLANET
    src/${PROJECT_NAME}/vt/planet/vts.h
    src/${PROJECT_NAME}/vt/planet/PlanetVT.h              src/${PROJECT_NAME}/vt/planet/PlanetVT.cpp
    src/${PROJECT_NAME}/vt/planet/PlanetPlatesVT.h        src/${PROJECT_NAME}/vt/planet/PlanetPlatesVT.cpp
    src/${PROJECT_NAME}/vt/planet/PlanetElevationVT.h     src/${PROJECT_NAME}/vt/planet/PlanetElevationVT.cpp
    src/${PROJECT_NAME}/vt/planet/PlanetCubeMapVT.h       src/${PROJECT_NAME}/vt/planet/PlanetCubeMapVT.cpp
    src/${PROJECT_NAME}/vt/planet/PlanetFaceColorVT.h     src/${PROJECT_NAME}/vt/planet/PlanetFaceColorVT.cpp
    src/${PROJECT_NAME}/vt/planet/PlanetVectorsVT.h       src/${PROJECT_NAME}/vt/planet/PlanetVectorsVT.cpp
    src/${PROJECT_NAME}/vt/planet/PlanetWireFrameVT.h     src/${PROJECT_NAME}/vt/planet/PlanetWireFrameVT.cpp
)

set(SRC_GEO_PLANET_DEMO_VT_PLANET_HELPER
    src/${PROJECT_NAME}/vt/planet/helper/PlateColorizer.h src/${PROJECT_NAME}/vt/planet/helper/PlateColorizer.cpp
)

set(SRC_GEO_PLANET_DEMO_INTERFACES
    src/${PROJECT_NAME}/interfaces/LoggerInterface.h
    src/${PROJECT_NAME}/interfaces/MainLoopInterface.h
    src/${PROJECT_NAME}/interfaces/RendererInterface.h
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

source_group("GeoPlanetDemo"                     FILES ${SRC_GEO_PLANET_DEMO})
source_group("GeoPlanetDemo\\core"               FILES ${SRC_GEO_PLANET_DEMO_CORE})
source_group("GeoPlanetDemo\\scene"              FILES ${SRC_GEO_PLANET_DEMO_SCENE})
source_group("GeoPlanetDemo\\scene\\entities"    FILES ${SRC_GEO_PLANET_DEMO_SCENE_ENTITIES})
source_group("GeoPlanetDemo\\vt"                 FILES ${SRC_GEO_PLANET_DEMO_VT})
source_group("GeoPlanetDemo\\vt\\planet"         FILES ${SRC_GEO_PLANET_DEMO_VT_PLANET})
source_group("GeoPlanetDemo\\vt\\planet\\helper" FILES ${SRC_GEO_PLANET_DEMO_VT_PLANET_HELPER})
source_group("GeoPlanetDemo\\sdl"                FILES ${SRC_GEO_PLANET_DEMO_SDL})
source_group("GeoPlanetDemo\\interfaces"         FILES ${SRC_GEO_PLANET_DEMO_INTERFACES})

source_group("vendor\\stb"   FILES ${SRC_VENDOR_STB})
source_group("vendor\\imgui" FILES ${SRC_VENDOR_IAMGUI})

# generate shader definitions from SHADER_FILES based on their location
set(SHADER_COMPILE_DEFINITIONS )
foreach(FILE_RELATIVE_NAME ${SHADER_FILES})

   unset(shader_file CACHE)

    # find full name of shader
    find_file(shader_file
        ${FILE_RELATIVE_NAME}
        HINTS ${${PROJECT_NAME}_RESOURCES}/shaders
    )

    # create shader definition string
    string(REPLACE "/" "_" definition_name ${FILE_RELATIVE_NAME})
    string(REPLACE "\\" "_" definition_name ${definition_name})
    string(REGEX REPLACE "\\..*" "" definition_name ${definition_name})
    string(TOUPPER ${definition_name} definition_name)
    string(CONCAT shader_definition
        "SHADER_" ${definition_name} "=\"" ${shader_file} "\""
    )

    string(CONCAT shader_definition_json
        "\"SHADER_" ${definition_name} "=\\\"" ${shader_file} "\\\"\","
    )

    message(${shader_definition_json})

    # add shader_definition to SHADER_COMPILE_DEFINITIONS list
    list(APPEND SHADER_COMPILE_DEFINITIONS ${shader_definition})
endforeach()

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${SRC_GEO_PLANET_DEMO}
    ${SRC_GEO_PLANET_DEMO_CORE}
    ${SRC_GEO_PLANET_DEMO_SCENE}
    ${SRC_GEO_PLANET_DEMO_SCENE_ENTITIES}
    ${SRC_GEO_PLANET_DEMO_VT}
    ${SRC_GEO_PLANET_DEMO_VT_PLANET}
    ${SRC_GEO_PLANET_DEMO_VT_PLANET_HELPER}
    ${SRC_GEO_PLANET_DEMO_SDL}
    ${SRC_GEO_PLANET_DEMO_INTERFACES}
    ${SRC_VENDOR_STB}
    ${SRC_VENDOR_IAMGUI}
)

target_link_libraries(${PROJECT_NAME}
    geGL
    geUtil
    SDL2CPP::SDL2CPP
    GeoPlanetLib::GeoPlanetLib
    glm
)

target_include_directories(${PROJECT_NAME}
    PRIVATE src
)

# texture files
find_file(coordCubeMapImage
    coords_cube_map.png
    HINTS ${${PROJECT_NAME}_RESOURCES}/textures
)

message("COORDS_CUBE_MAP=\"${coordCubeMapImage}\"")

# add macra definitions to code
target_compile_definitions(${PROJECT_NAME} PUBLIC
    ${SHADER_COMPILE_DEFINITIONS}
    $<$<CONFIG:DEBUG>: "GPD_DEBUG" "GPD_ENABLE_ASSERTS" >
    "COORDS_CUBE_MAP=\"${coordCubeMapImage}\""
)

include(CMakeCopyDlls.cmake)

install(DIRECTORY ${OUTPUT_BINDIR}/Release/ DESTINATION bin )
include(InstallRequiredSystemLibraries)
