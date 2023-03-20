cmake_minimum_required(VERSION 3.5)

project(Desktop_Creator_Demo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ICON_FOLDER ${CMAKE_CURRENT_BINARY_DIR}/.icon)
set(SOFTWARE_VERSION ${CMAKE_CURRENT_BINARY_DIR}/.version.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${ICON_FOLDER}")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory  "${CMAKE_CURRENT_SOURCE_DIR}/.icon" "${ICON_FOLDER}")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/.version.txt" "${SOFTWARE_VERSION}")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)



add_subdirectory(desktop_creator)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

add_executable(Desktop_Creator_Demo ${PROJECT_SOURCES})

target_include_directories(Desktop_Creator_Demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/desktop_creator)

target_link_libraries(Desktop_Creator_Demo PRIVATE Qt${QT_VERSION_MAJOR}::Widgets desktop_creator)

set_target_properties(Desktop_Creator_Demo PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Desktop_Creator_Demo)
endif()
