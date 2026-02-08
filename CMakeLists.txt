cmake_minimum_required(VERSION 3.31)
project(Elaborato_3_Lab_QT)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.10.2/mingw_64")

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

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX "")

    list(GET CMAKE_PREFIX_PATH 0 QT_BASE_DIR)
    file(TO_CMAKE_PATH "${QT_BASE_DIR}" QT_BASE_DIR)

    message(STATUS "Qt base directory: ${QT_BASE_DIR}")

    if(EXISTS "${QT_BASE_DIR}/bin/Qt6Core.dll")
        set(QT_BIN_DIR "${QT_BASE_DIR}/bin")
    elseif(EXISTS "${QT_BASE_DIR}/../../bin/Qt6Core.dll")
        get_filename_component(QT_BIN_DIR "${QT_BASE_DIR}/../../bin" ABSOLUTE)
    else()
        message(WARNING "Impossibile trovare le DLL Qt. L'app potrebbe non avviarsi.")
        set(QT_BIN_DIR "")
    endif()

    if(QT_BIN_DIR)
        if(EXISTS "${QT_BASE_DIR}/plugins/platforms/qwindows.dll")
            add_custom_command(TARGET Elaborato_3_Lab_QT POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "$<TARGET_FILE_DIR:Elaborato_3_Lab_QT>/plugins/platforms/"
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_BASE_DIR}/plugins/platforms/qwindows.dll"
                    "$<TARGET_FILE_DIR:Elaborato_3_Lab_QT>/plugins/platforms/"
                    COMMENT "Copiando Qt platform plugin..."
            )
        endif()

        foreach(QT_LIB Core Gui Widgets)
            if(EXISTS "${QT_BIN_DIR}/Qt6${QT_LIB}.dll")
                add_custom_command(TARGET Elaborato_3_Lab_QT POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy
                        "${QT_BIN_DIR}/Qt6${QT_LIB}.dll"
                        "$<TARGET_FILE_DIR:Elaborato_3_Lab_QT>"
                        COMMENT "Copiando Qt6${QT_LIB}.dll..."
                )
            endif()
        endforeach()
    endif()
endif()

