#include <ros/ros.h>
#include <std_msgs/String.h>
#include <bruno/ModelState.h>
#include <bruno/ModelStates.h>
#include <geometry_msgs/Pose.h>
#include <bruno/SpawnModel.h>

#include <sstream>
/**
* This tutorial demonstrates simple sending of messages over the ROS system.
*/
int main(int argc, char **argv)
{
    /**
* The ros::init() function needs to see argc and argv so that it can perform
* any ROS arguments and name remapping that were provided at the command line.
* For programmatic remappings you can use a different version of init() which takes
* remappings directly, but for most command-line programs, passing argc and argv is
* the easiest way to do it.  The third argument to init() is the name of the node.
*
* You must call one of the versions of ros::init() before using any other
* part of the ROS system.
*/
ros::init(argc, argv, "bruno_node");

/**
* NodeHandle is the main access point to communications with the ROS system.
* The first NodeHandle constructed will fully initialize this node, and the last
* NodeHandle destructed will close down the node.
*/
ros::NodeHandle bruno_node;

/**
* The advertise() function is how you tell ROS that you want to
* publish on a given topic name. This invokes a call to the ROS
* master node, which keeps a registry of who is publishing and who
* is subscribing. After this advertise() call is made, the master
* node will notify anyone who is trying to subscribe to this topic name,
* and they will in turn negotiate a peer-to-peer connection with this
* node.  advertise() returns a Publisher object which allows you to
* publish messages on that topic through a call to publish().  Once
* all copies of the returned Publisher object are destroyed, the topic
* will be automatically unadvertised.
*
* The second parameter to advertise() is the size of the message queue
* used for publishing messages.  If messages are published more quickly
* than we can send them, the number here specifies how many messages to
* buffer up before throwing some away.
*/
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

/**
* A count of how many messages we have sent. This is used to create
* a unique string for each message.
*/
int lap_half =1;
while (ros::ok())
{
        /**
    * This is a message object. You stuff it with data, and then publish it.
    */
    
    
     
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

    /**
    * The publish() function is how you send messages. The parameter
    * is the message object. The type of this object must agree with the type
    * given as a template parameter to the advertise<>() call, as was done
    * in the constructor above.

    */

    
    ROS_INFO("state published!");


    ros::spinOnce();



    loop_rate.sleep();

}

return 0;
}