
cmake_minimum_required(VERSION 3.7)

# Check if we are building as stand-alone project
# condition from https://stackoverflow.com/questions/13289314/cmake-check-if-the-main-project-was-called
if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  project(
    GPUTerrainDemo
    VERSION 0.0.0
    )
endif()

set(APP_NAME "TerrainDemo")

set(CMAKE_AUTOMOC ON)

find_package(GPUEngine  COMPONENTS  REQUIRED geGL geUtil)
find_package(Qt5        COMPONENTS  REQUIRED Gui)
find_package(GPUTerrain CONFIG      REQUIRED)

set(DEFAULT_RESOERCES_PATH "${CMAKE_CURRENT_LIST_DIR}/resources")
set(${APP_NAME}_RESOURCES  "${DEFAULT_RESOERCES_PATH}" CACHE PATH "Relative or absolute path to Application resources.")

set(SOURCES
  src/main.cpp
  src/OpenGLWindow.h src/OpenGLWindow.cpp
)

# find shader file paths
find_file(vertexShader vertexShader.glsl
  HINTS ${${APP_NAME}_RESOURCES}/shaders
)

find_file(fragmentShader fragmentShader.glsl
  HINTS ${${APP_NAME}_RESOURCES}/shaders
)

link_directories(
  "d:/MyProjects/GPUEngine_all/_build/GPUTerrain/GPUTerrain/Debug"
)

add_executable(${APP_NAME} ${SOURCES})
target_link_libraries(${APP_NAME}
  Qt5::Gui
  geGL geUtil
  glm
  GPUTerrain
)
target_include_directories(${APP_NAME} PUBLIC "src/")

target_compile_definitions(${APP_NAME} PUBLIC
  "VERTEX_SHADER=\"${vertexShader}\""
  "FRAGMENT_SHADER=\"${fragmentShader}\""
)
