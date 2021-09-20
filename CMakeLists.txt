cmake_minimum_required(VERSION 3.17)
project(HelloSFML)

set(CMAKE_CXX_STANDARD 14)

# Handles the regular main.cpp
add_executable(HelloSFML main.cpp)

# Handles our tic tac toe game
add_executable(Pong pongSFML.cpp)

set(SFML_STATIC_LIBRARIES TRUE) # Copies the provided DLLS directly into our exe.
set(SFML_DIR C:/SFML/lib/cmake/SFML) # Setups path to additional make files.
find_package(SFML COMPONENTS system window graphics audio network REQUIRED) # Parts that we want.

include_directories(C:/SFML/include) # The headers
target_link_libraries(HelloSFML sfml-system sfml-window sfml-graphics sfml-audio sfml-network) # Uses links to our exe
target_link_libraries(Pong sfml-system sfml-window sfml-graphics sfml-audio sfml-network) # Uses links to our exe
