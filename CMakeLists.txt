
cmake_minimum_required(VERSION 3.7)

set(PROJECT_NAME "GPUTerrainDemo")
set(APP_NAME "TerrainDemo")

project(${PROJECT_NAME})

set(CMAKE_AUTOMOC ON)

find_package(GPUEngine COMPONENTS REQUIRED geGL)
find_package(Qt5 COMPONENTS REQUIRED Gui)

set(SOURCE_FILES
    src/main.cpp
    src/OpenGLWindow.h src/OpenGLWindow.cpp
)

add_executable(${APP_NAME} ${SOURCE_FILES})
target_link_libraries(${APP_NAME} Qt5::Gui geGL)
target_include_directories(${APP_NAME} PUBLIC PUBLIC "src/")
