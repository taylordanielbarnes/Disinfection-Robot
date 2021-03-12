# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
project(uvc)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)
#find_package(WiringPi REQUIRED)
#find_package(Threads REQUIRED)

find_library(wiringPi_LIB wiringPi)

## Declare ROS messages and services
#add_message_files(FILES Num.msg)
add_service_files(FILES set_lamp.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS} ${WIRINGPI_INCLUDE_DIRS})

#add_executable(talker src/talker.cpp)
#target_link_libraries(talker ${catkin_LIBRARIES})

#add_executable(listener src/listener.cpp)
#target_link_libraries(listener ${catkin_LIBRARIES})

## Build service client and server
# %Tag(SRVCLIENT)%
add_executable(uvc_server src/server.cpp)
#target_link_libraries(uvc_service ${catkin_LIBRARIES} ${WIRINGPI_LIBRARIES})
target_link_libraries(uvc_server ${catkin_LIBRARIES} ${wiringPi_LIB})
add_dependencies(uvc_server uvc_gencpp)

add_executable(uvc_client src/client.cpp)
target_link_libraries(uvc_client ${catkin_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
add_dependencies(uvc_client uvc_gencpp)

# %EndTag(SRVCLIENT)%

# %EndTag(FULLTEXT)%
