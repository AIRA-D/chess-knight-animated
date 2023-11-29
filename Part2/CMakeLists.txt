cmake_minimum_required(VERSION 3.26)
project(Knight)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Knight
        main.cpp
        knight.png
        ChessKnightPassFinder.cpp
        ChessKnightPassFinder.h
)
target_link_libraries(Knight
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

