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
    tictactoe/Minimax.cpp
    tictactoe/UI.cpp
    tictactoe/Board.cpp
)

set(HEADERS
    tictactoe/Board.hpp
    tictactoe/Minimax.hpp
    tictactoe/UI.hpp
    tictactoe/Cell.hpp
    tictactoe/Move.hpp

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
