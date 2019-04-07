cmake_minimum_required(VERSION 2.6)
project(lane_cnn)

find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(lane_cnn main.cpp)
target_link_libraries(Qt5::Core)
target_link_libraries(Qt5::Widgets)
target_link_libraries( lane_cnn ${TORCH_LIBRARIES} ${OpenCV_LIBS})
install(TARGETS lane_cnn RUNTIME DESTINATION bin)
