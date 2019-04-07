cmake_minimum_required(VERSION 2.6)
project(lane_classic)

find_package(OpenCV REQUIRED)

add_executable(lane_classic main.cpp)
target_link_libraries( lane_classic ${OpenCV_LIBS} )
install(TARGETS lane_classic RUNTIME DESTINATION bin)
