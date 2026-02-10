cmake_minimum_required(VERSION 3.31)
project(Elaborato_3_Lab_QT)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS
        Core
        Gui
        Widgets
        )

add_library(activitytracker_lib STATIC
        Activity.cpp
        Activity.h
        ActivityTracker.cpp
        ActivityTracker.h
        MainWindow.cpp
        MainWindow.h
)

target_link_libraries(activitytracker_lib
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

add_executable(Elaborato_3_Lab_QT
        main.cpp
)

target_link_libraries(Elaborato_3_Lab_QT
        activitytracker_lib
)

option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(Test)
endif()
