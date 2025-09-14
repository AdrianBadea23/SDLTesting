cmake_minimum_required(VERSION 3.12)
project(MyProgram VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(MyProgram src/main.cpp 
                src/RenderWindow.cpp 
                src/Entity.cpp
                src/Math.cpp)

# Include SDL2 headers
target_include_directories(MyProgram PRIVATE
                            ${SDL2_INCLUDE_DIRS}
                            ${SDL2_IMAGE_INCLUDE_DIRS}
                            ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link SDL2 library
target_link_libraries(MyProgram PRIVATE 
                            ${SDL2_LIBRARIES}
                            ${SDL2_IMAGE_LIBRARIES}
                            SDL2_image)
