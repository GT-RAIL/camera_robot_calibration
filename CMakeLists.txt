cmake_minimum_required(VERSION 2.8.3)
project(camera_robot_calibration)
find_package(catkin REQUIRED COMPONENTS rospy std_msgs tf geometry_msgs tf_conversions rviz roscpp)

## This plugin includes Qt widgets, so we must include Qt
find_package(Qt4 REQUIRED COMPONENTS
  QtCore
  QtGui
)

catkin_python_setup()
catkin_package()

## Specify additional locations of header files
include_directories(include
  ${catkin_INCLUDE_DIRS}
)

## Include for use with Qt
include(${QT_USE_FILE})

## For use with Qt signals and slots
add_definitions(-DQT_NO_KEYWORDS)

## Specify which header files need to be run through "moc" (Qt's meta-object compiler).
qt4_wrap_cpp(MOC_FILES
  include/camera_robot_calibration/CalibrationPanel.h
)

## Specify plugin source files
set(SOURCE_FILES
  src/CalibrationPanel.cpp
  ${MOC_FILES}
)

## Declare a cpp library
add_library(${PROJECT_NAME} ${SOURCE_FILES})

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  ${QT_LIBRARIES}
)

## Mark executables and/or libraries for installation
install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

## Copy header files
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)

## Copy launch files
install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
  FILES_MATCHING PATTERN "*.launch"
)

## Copy rviz files
install(DIRECTORY rviz/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/rviz
  FILES_MATCHING PATTERN "*.rviz"
)

## Copy plugin config files
install(FILES plugin_description.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(PROGRAMS scripts/camera_robot_calibration.py DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})