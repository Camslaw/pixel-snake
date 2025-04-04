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
    set(VCPKG_ROOT ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}$<$<CONFIG:Debug>:/debug>)
    set(BIN_DIR ${VCPKG_ROOT}/bin)
    set(IMPORT_DIR ${VCPKG_ROOT}/Qt6/qml)
    set(PATH_DIR ${VCPKG_ROOT}/Qt6/plugins)
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${BIN_DIR}\nQML_IMPORT_PATH=${IMPORT_DIR}\nQT_PLUGIN_PATH=${PATH_DIR}")
endif()

