cmake_minimum_required(VERSION 3.8)
project(LawnGrower)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)


# Add source files
set(SOURCES
    Canvas.cpp
    FlowerColors.cpp
    Point.cpp
    TextureZone.cpp
    Image.cpp
    Color.cpp
)

# Add header files
set(HEADERS
    Canvas.hpp
    FlowerColors.hpp
    Point.hpp
    TextureZone.hpp
    Image.hpp
    Color.hpp
)

add_executable(LawnGrower "main.cpp"
    ${SOURCES} 
    ${HEADERS}
)