cmake_minimum_required(VERSION 3.0.2)
project(detector_switch_ros)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  image_transport
  sensor_msgs
  image_geometry
  geometry_msgs
  cv_bridge
)


find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS ON) #...with compiler extensions like gnu++11


catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp rospy std_msgs cv_bridge sensor_msgs image_transport geometry_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

file(GLOB SOURCES
                src/detector_switch_node.cpp
                src/detector_switch.cpp
)


add_executable(${PROJECT_NAME}_node ${SOURCES})
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})

add_executable(start_landing_service
  src/service_land.cpp
)
target_link_libraries(start_landing_service ${catkin_LIBRARIES})

