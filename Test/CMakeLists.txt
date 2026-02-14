cmake_minimum_required(VERSION 3.31)
project(ActivityTrackerTest)

include(FetchContent) #necessario per ottenere la versione corretta di Google-test

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)

set(gtest_force_shared_ctr ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
message(STATUS "Google Test is been configured by FetchContent")

add_executable(activitytracker_tests
        Unit/ActivityTrackerTest.cpp
        )

set_target_properties(activitytracker_tests PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
)

target_include_directories(activitytracker_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(activitytracker_tests
        activitytracker_lib
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        gtest
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(activitytracker_tests
        TEST_PREFIX ""
        TEST_SUFFIX ""
        PROPERTIES
        TIMEOUT 30
        LABELS "unit"
)

message(STATUS "Configured Tests: executable ${CMAKE_CURRENT_BINARY_DIR}/bin/activitytracker_tests")
