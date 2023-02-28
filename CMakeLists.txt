cmake_minimum_required(VERSION 3.5)

project(desktop_creator VERSION 0.1 LANGUAGES CXX)

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

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        desktop_creator.cpp
        desktop_creator.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(desktop_creator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET desktop_creator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(desktop_creator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(desktop_creator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(desktop_creator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(desktop_creator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(desktop_creator)
endif()
