cmake_minimum_required(VERSION 3.28)

project(PixelSnake)

add_executable(PixelSnake src/main.cpp)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)