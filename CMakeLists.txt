cmake_minimum_required(VERSION 3.28)

project(PixelSnake)

add_executable(PixelSnake src/main.cpp)

find_package(Qt6 REQUIRED COMPONENTS Quick)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Quick
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
set_target_properties(PixelSnake PROPERTIES VS_DEBUGGER_ENVIRONMENT "QT_PLUGIN_PATH=${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug/Qt6/plugins")
endif()