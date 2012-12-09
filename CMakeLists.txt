cmake_minimum_required(VERSION 2.8)
project(ConnectFour)

set(cf_sources board.cpp uInterface.cpp main.cpp)

add_executable(connectfour ${cf_sources})

set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(SFML 2 COMPONENTS graphics system window REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(connectfour ${SFML_LIBRARIES})
