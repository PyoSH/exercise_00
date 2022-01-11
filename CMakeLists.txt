cmake_minimum_required(VERSION 2.8.3)
project(exercise_00)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  image_transport
  cv_bridge
  message_generation
)

find_package(OpenCV REQUIRED)


add_message_files(
  DIRECTORY /home/catkin_ws/src/exercise_00/msg
  FILES 
  VidInfo.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

include_directories(${OpenCV_INCLUDE_DIRS})


catkin_package(
  CATKIN_DEPENDS
    rospy
    std_msgs
    message_runtime
)

include_directories(${catkin_INCLUDE_DIRS})


add_executable(exercise_00_pub src/exercise_00_pub.cpp)
add_executable(exercise_00_sub src/exercise_00_sub.cpp)


target_link_libraries(exercise_00_pub ${catkin_LIBRARIES})
target_link_libraries(exercise_00_pub ${OpenCV_LIBS})

target_link_libraries(exercise_00_sub ${catkin_LIBRARIES})
target_link_libraries(exercise_00_sub ${OpenCV_LIBS})


