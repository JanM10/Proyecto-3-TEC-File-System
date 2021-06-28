cmake_minimum_required(VERSION 3.14)

project(ControllerNode LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5 COMPONENTS REQUIRED Core)

add_executable(ControllerNode
    main.cpp
    controllernodesocket.cpp
    controllernodesocket.h
    controllernodeserver.cpp
    controllernodeserver.h
)

target_link_libraries(ControllerNode Qt5::Core)
target_link_libraries(ControllerNode Qt5::Widgets)
target_link_libraries(ControllerNode Qt5::Network)
