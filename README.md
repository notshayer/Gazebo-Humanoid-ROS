# Gazebo-Humanoid-ROS


`git clone https://github.com/notshayer/Gazebo-Humanoid-ROS.git`
`cd Gazebo-Humanoid-ROS`
`cp bruno $ROS_WS/src`
`cd $ROS_WS`
`catkin build bruno`

`roslaunch system_config mavros_posix_sitl.launch`
`rosrun bruno bruno_node`  >>>  spawns the humanoid model and loops him repeatedly through a set course.
