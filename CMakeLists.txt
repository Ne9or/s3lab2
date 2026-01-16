cmake_minimum_required(VERSION 3.16)

project(TicTacToe LANGUAGES CXX)

# стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# предупреждения
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# исходники
set(SOURCES
    main.cpp
    tictactoe/Minimax.cpp
    tictactoe/UI.cpp
    tictactoe/Board.cpp
)

# заголовки (для IDE)
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

add_executable(TicTacToe
    ${SOURCES}
    ${HEADERS}
)

# пути для #include
target_include_directories(TicTacToe PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tictactoe
    ${CMAKE_CURRENT_SOURCE_DIR}/sequence
)
