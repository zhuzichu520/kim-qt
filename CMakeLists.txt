cmake_minimum_required(VERSION 3.20)

project(kim VERSION 0.1 LANGUAGES CXX)

set(FLUENTUI_BUILD_EXAMPLES OFF)
set(protobuf_BUILD_TESTS OFF)
set(protobuf_BUILD_PROTOC_BINARIES OFF)
set(protobuf_WITH_ZLIB OFF)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MT>
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
    )
endif()

add_subdirectory(src)
add_subdirectory(protobuf/cmake)
add_subdirectory(FluentUI)
