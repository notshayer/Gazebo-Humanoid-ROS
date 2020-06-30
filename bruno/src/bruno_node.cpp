#include <ros/ros.h>
#include <std_msgs/String.h>
#include <bruno/ModelState.h>
#include <bruno/ModelStates.h>
#include <geometry_msgs/Pose.h>
#include <bruno/SpawnModel.h>
#include <ros/package.h>

#include <sstream>

int main(int argc, char **argv)
{
    // initialize and define node handle
    ros::init(argc, argv, "bruno_node");
    ros::NodeHandle bruno_node;
    std::string path = ros::package::getPath("bruno");
    const char* upath = path.c_str();
    
    //model spawner ---> should probaly use rosservice call.... eventually
    int spawn_count = 0;
    if (spawn_count==0)
    {
        system((std::string("rosrun gazebo_ros spawn_model -file ")+path+std::string("/src/bruno/bruno_model/model.sdf -sdf -model bruno -y 0 -x -3.1")).c_str());
        spawn_count = 1;
    }

    // defines publisher <message type> (rostopic, queue size)
    ros::Publisher bruno_control = bruno_node.advertise<bruno::ModelState>("gazebo/set_model_state", 100);
    // defines the update rate, which in this case is a parameter that affects 
    ros::Rate loop_rate(10);
    //defines initial message variable as appropriate variable type, then sets initial world pose parameters
    bruno::ModelState state;
    state.model_name = "bruno";
    state.pose.position.x = 3.5;
    state.pose.position.y = 0;
    state.pose.position.z = 0;
    state.pose.orientation.z = -1.57;

    int lap_half =1;
    while (ros::ok())
    {
        // if statements that cause model to loop back and forth across a line
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
        // publishes to node after pose states updates, and logs statuses, then repeats loop
        bruno_control.publish(state);
        ROS_INFO("pose received!");
        ROS_INFO("state published!");
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}