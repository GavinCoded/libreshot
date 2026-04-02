cmake_minimum_required(VERSION 3.20)
project(libreshot VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets DBus Svg Network)
find_package(PkgConfig REQUIRED)
find_package(LayerShellQt REQUIRED)
pkg_check_modules(PIPEWIRE REQUIRED IMPORTED_TARGET libpipewire-0.3)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE RESOURCES src/*.qrc)

add_executable(libreshot ${SOURCES} ${HEADERS} ${RESOURCES})

target_include_directories(libreshot PRIVATE src)
target_link_libraries(libreshot PRIVATE
    Qt6::Widgets Qt6::DBus Qt6::Svg Qt6::Network PkgConfig::PIPEWIRE
    LayerShellQt::Interface)
