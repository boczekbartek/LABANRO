#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <std_msgs/String.h>




void chatterCallback(const sensor_msgs::JointStateConstPtr &msg)
{
 
  ROS_INFO("Positions from JSP: [%f %f %f]", msg->position[0],msg->position[1],msg->position[2]);
  

}

int main(int argc, char** argv) {
    ros::init(argc, argv, "checker");
    ros::NodeHandle n;
 
    ros::Subscriber sub = n.subscribe<sensor_msgs::JointState>("pozycje_jointow", 1000, 
                                                               boost::bind(chatterCallback,_1)); 

    ros::spin();
    return 0;
}
