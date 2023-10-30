cmake_minimum_required(VERSION 3.20)

project(kim VERSION 0.1 LANGUAGES CXX)

set(FLUENTUI_BUILD_EXAMPLES OFF)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

add_subdirectory(src)
add_subdirectory(core)
add_subdirectory(FluentUI)
