project(digizerReadout)


cmake_minimum_required(VERSION 3.0)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT 6.22 CONFIG REQUIRED)

include(${ROOT_USE_FILE})

add_executable(digizerReadout main.cpp eventTools.cpp)

target_link_libraries(digizerReadout ${ROOT_LIBRARIES})
