cmake_minimum_required(VERSION 3.10)
project(CellGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH )
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH "D:\\install\\mingwsecond\\5.12.8\\mingw73_64\\")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(CellGame main.cpp src/ui/window/mainwindow/MainWindow.h src/ui/window/mainwindow/MainWindow.cpp src/ui/widget/game/GameWidget.cpp src/ui/widget/game/GameWidget.h src/include/Config.h src/utility/Rand_int.h src/utility/CellGameCore.cpp src/utility/CellGameCore.h src/test/utility/CellGameCoreTest.cpp)
target_link_libraries(CellGame Qt5::Widgets)
qt5_use_modules(CellGame Core Widgets Gui)

add_subdirectory(googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)
target_link_libraries(CellGame gtest gtest_main)
target_link_libraries(CellGame gmock gmock_main)

add_executable(mytest src/test/utility/CellGameCoreTest.cpp src/utility/CellGameCore.cpp)
target_link_libraries(mytest gtest gtest_main)