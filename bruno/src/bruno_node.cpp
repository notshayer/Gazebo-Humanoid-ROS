#include <ros/ros.h>
#include <std_msgs/String.h>
#include <bruno/ModelState.h>
#include <bruno/ModelStates.h>
#include <geometry_msgs/Pose.h>
#include <bruno/SpawnModel.h>

#include <sstream>

int main(int argc, char **argv)
{

ros::init(argc, argv, "bruno_node");

ros::NodeHandle bruno_node;

int spawn_count = 0;
if (spawn_count==0)
{
    system("rosrun gazebo_ros spawn_model -file `echo $ROS_WS`/src/bruno/bruno_model/model.sdf -sdf -model bruno -y 0 -x -3.1");
    spawn_count = 1;
}


ros::Publisher bruno_control = bruno_node.advertise<bruno::ModelState>("gazebo/set_model_state", 100);

ros::Rate loop_rate(10);

bruno::ModelState state;
state.model_name = "bruno";
state.pose.position.x = 3.5;
state.pose.position.y = 0;
state.pose.position.z = 0;
state.pose.orientation.z = -1.57;


int lap_half =1;
while (ros::ok())
{
    
    
     
    if (state.pose.position.y > -6 && lap_half ==1)
    {
        state.pose.position.y = state.pose.position.y - 0.1;
        if (state.pose.position.y < -6)
        {
            lap_half = 2;
            // state.pose.orientation.z = state.pose.orientation.z+1.57/2;
            loop_rate.sleep();
        }
        
    }
    else if (lap_half ==2)
    {
        state.pose.position.y = state.pose.position.y + 0.1;
        if (state.pose.position.y > 1.5)
        {
            lap_half = 1;
            // state.pose.orientation.z = state.pose.orientation.z-1.57/2;
        }
    }
    bruno_control.publish(state);
    ROS_INFO("pose received!");
    
    ROS_INFO("state published!");

    ros::spinOnce();

    loop_rate.sleep();
}

return 0;
}