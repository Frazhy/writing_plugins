cmake_minimum_required(VERSION 3.0.2)
project(writing_plugins)

find_package(gazebo REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  gazebo_plugins
  gazebo_ros
  roscpp
)

catkin_package()

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(my_gazebo_plugin SHARED src/my_gazebo_plugin.cc)
target_link_libraries(my_gazebo_plugin ${GAZEBO_LIBRARIES})

add_library(world_plugin SHARED src/world_plugin.cc)
target_link_libraries(world_plugin ${GAZEBO_LIBRARIES})
