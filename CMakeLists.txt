cmake_minimum_required(VERSION 3.15)
project(BaccaratSimulator VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(baccarat
        src/main.cpp
        src/Card.cpp
        src/Deck.cpp
        src/BaccaratGame.cpp
        src/Player.cpp
        src/Scoreboard.cpp
        src/Statistics.cpp
        src/Display.cpp
)

target_include_directories(baccarat PRIVATE include)
