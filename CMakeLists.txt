cmake_minimum_required(VERSION 3.28)

project(PixelSnake)

# Autogen (moc, rcc)
set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/GameController.cpp
    src/GameController.h
    qml/qml.qrc
)

find_package(Qt6 REQUIRED COMPONENTS Quick)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Quick
)

qt_add_resources(${PROJECT_NAME} "qml"
        PREFIX "/"
        FILES qml/main.qml
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
