
cmake_minimum_required(VERSION 3.12.4)

project(
    GPUTerrainProject-Demo
    VERSION 0.0.0
)

set(APP_NAME "TerrainDemo")

set(SDL2_BUILDING_LIBRARY ON)
find_package(SDL2 CONFIG QUIET)

if(NOT SDL2_FOUND)
   return()
endif()

if(NOT TARGET GPUEngine)
    find_package(GPUEngine  COMPONENTS  REQUIRED geCore geGL geUtil SDLWindow)
endif()

if(NOT TARGET GPUTerrain)
    find_package(GPUTerrain CONFIG REQUIRED)
endif()

if(NOT TARGET glfw)
    find_package(glfw CONFIG REQUIRED)
endif()

set(DEFAULT_RESOERCES_PATH "${CMAKE_CURRENT_LIST_DIR}/resources")
set(${APP_NAME}_RESOURCES  "${DEFAULT_RESOERCES_PATH}" CACHE PATH "Relative or absolute path to Application resources.")

file(GLOB TERRAIN_DEMO_HEADERS    src/${APP_NAME}/*.h)
file(GLOB TERRAIN_DEMO_SOURCES    src/${APP_NAME}/*.cpp)
file(GLOB TERRAIN_DEMO_INTERFACES src/${APP_NAME}/Interfaces/*.h)

source_group("Interfaces" FILES ${TERRAIN_DEMO_INTERFACES})

message(${TERRAIN_DEMO_HEADERS})
message(${TERRAIN_DEMO_SOURCES})
message(${TERRAIN_DEMO_INTERFACES})

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
    SDLWindow
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
    # GPUEngine *.dll
    get_target_property(GPUEngine_geCore_Location    geCore    LOCATION)
    get_target_property(GPUEngine_geGL_Location      geGL      LOCATION)
    get_target_property(GPUEngine_geUtil_Location    geUtil    LOCATION)
    # get_target_property(GPUEngine_SDLWindow_Location SDLWindow LOCATION)
    # GPUEngine *d.dll
    get_target_property(GPUEngine_geCore_LocationDebug    geCore    IMPORTED_LOCATION_DEBUG)
    get_target_property(GPUEngine_geGL_LocationDebug      geGL      IMPORTED_LOCATION_DEBUG)
    get_target_property(GPUEngine_geUtil_LocationDebug    geUtil    IMPORTED_LOCATION_DEBUG)
    # get_target_property(GPUEngine_SDLWindow_LocationDebug SDLWindow IMPORTED_LOCATION_DEBUG)

    # # GPUTerrain *.dll
    # get_target_property(GPUTerrain_Location GPUTerrain LOCATION)
    # # GPUTerrain *d.dll
    # get_target_property(GPUTerrain_LocationDebug GPUTerrain IMPORTED_LOCATION_DEBUG)

    add_custom_command(TARGET ${APP_NAME} POST_BUILD
        # GPUEngine
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<$<CONFIG:Debug>:${GPUEngine_geCore_LocationDebug}> $<$<NOT:$<CONFIG:Debug>>:${GPUEngine_geCore_Location}> $<TARGET_FILE_DIR:${APP_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<$<CONFIG:Debug>:${GPUEngine_geGL_LocationDebug}> $<$<NOT:$<CONFIG:Debug>>:${GPUEngine_geGL_Location}> $<TARGET_FILE_DIR:${APP_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<$<CONFIG:Debug>:${GPUEngine_geUtil_LocationDebug}> $<$<NOT:$<CONFIG:Debug>>:${GPUEngine_geUtil_Location}> $<TARGET_FILE_DIR:${APP_NAME}>
        # COMMAND ${CMAKE_COMMAND} -E copy_if_different $<$<CONFIG:Debug>:${GPUEngine_SDLWindow_LocationDebug}> $<$<NOT:$<CONFIG:Debug>>:${GPUEngine_SDLWindow_Location}> $<TARGET_FILE_DIR:${APP_NAME}>
        # # GPUTerrain
        # COMMAND ${CMAKE_COMMAND} -E copy_if_different $<$<TARGET_FILE>:GPUTErrain> $<$<NOT:$<CONFIG:Debug>>:${GPUTerrain_Location}> $<TARGET_FILE_DIR:${APP_NAME}>
    )
endif()
