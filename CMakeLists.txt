cmake_minimum_required(VERSION 3.10)
project(MUHPGE)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(${PROJECT_NAME} main.cc ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} ${Geant4_LIBRARIES})