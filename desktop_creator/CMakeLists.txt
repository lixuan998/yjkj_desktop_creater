cmake_minimum_required(VERSION 3.5)

project(desktop_creator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_library(desktop_creator STATIC desktop_creator.cpp)

target_link_libraries(desktop_creator Qt${QT_VERSION_MAJOR}::Widgets)