cmake_minimum_required(VERSION 3.16)

project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(SOURCES
    main.cpp
    tictactoe/UI.cpp
    tictactoe/Board.cpp
    tictactoe/GameTree.cpp
)

set(HEADERS
    tictactoe/Board.hpp
    tictactoe/UI.hpp
    tictactoe/Node.hpp
    tictactoe/GameTree.hpp

    sequence/Sequence.hpp
    sequence/ArraySequence.hpp
    sequence/DynamicArray.hpp
)

add_executable(main
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tictactoe
    ${CMAKE_CURRENT_SOURCE_DIR}/sequence
)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests
    tests.cpp
    tictactoe/Board.cpp 
    tictactoe/GameTree.cpp
)

target_include_directories(tests
    PRIVATE
        ${PROJECT_INCLUDE_DIR}
)

target_link_libraries(tests
    PRIVATE
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)