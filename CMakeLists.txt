
cmake_minimum_required(VERSION 3.7)

set(APP_NAME "TerrainDemo")

project(
  GPUTerrainDemo
  VERSION 0.0.0
  )

set(CMAKE_AUTOMOC ON)

find_package(GPUEngine COMPONENTS REQUIRED geGL)
find_package(Qt5 COMPONENTS REQUIRED Gui)
find_package(GPUTerrain CONFIG REQUIRED)

set(DEFAULT_RESOERCES_PATH "${CMAKE_CURRENT_LIST_DIR}/resources")
set(${APP_NAME}_RESOURCES "${DEFAULT_RESOERCES_PATH}" CACHE PATH "Relative or absolute path to Application resources.")

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

add_executable(${APP_NAME} ${SOURCES})
target_link_libraries(${APP_NAME} Qt5::Gui geGL GPUTerrain::GPUTerrain)
target_include_directories(${APP_NAME} PUBLIC PUBLIC "src/")

target_compile_definitions(${APP_NAME} PUBLIC
  "VERTEX_SHADER=\"${vertexShader}\""
  "FRAGMENT_SHADER=\"${fragmentShader}\""
)
