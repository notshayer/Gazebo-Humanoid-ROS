# Gazebo-Humanoid-ROS


`git clone https://github.com/notshayer/Gazebo-Humanoid-ROS.git` <br />
`cd Gazebo-Humanoid-ROS` <br />
`cp bruno $ROS_WS/src` <br />
`cd $ROS_WS` <br />
`catkin build bruno` <br />

`roslaunch system_config mavros_posix_sitl.launch` <br />
`rosrun bruno bruno_node`  >>>  spawns the humanoid model and loops him repeatedly through a set course.
