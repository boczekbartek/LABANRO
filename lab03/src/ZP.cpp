#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <sensor_msgs/JointState.h>
#include "lab03/kinematics.h"

typedef struct kinematicsManagmentStruct
{
    bool use_kdl;
    ros::Publisher *marker_pub;
    ros::ServiceClient *kdl_client;
    ros::ServiceClient *simple_client;
} KinStruct;

void joint_states_cb(const sensor_msgs::JointStateConstPtr &msg, KinStruct k)
{
    anrobot_description::kinematics srv; //new folder srv added (relatively to lab02)
    srv.request.theta1 = msg->position[0];
    srv.request.theta2 = msg->position[1];
    srv.request.d3 = msg->position[2];
    srv.request.use_kdl = k.use_kdl;

    //BB, marker description: http://wiki.ros.org/rviz/Tutorials/Markers%3A%20Basic%20Shape
    visualization_msgs::Marker marker;
    marker.header.frame_id = "/last_pose";
    marker.header.stamp = ros::Time::now();

    marker.ns = "last_position";
    marker.id = 0;
    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = visualization_msgs::Marker::SPHERE;
    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;
    
    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.1;
    marker.scale.y = 0.1;
    marker.scale.z = 0.1;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

     if(srv.request.use_kdl)
      {
          if(k.kdl_client->call(srv))
           {
              marker.pose = srv.response.last_position;
           }
      }
     else
      {
          if(k.simple_client->call(srv))
           {
              marker.pose = srv.response.last_position;
           }
      }
      k.marker_pub->publish(marker);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "set_param");
    if(argc != 2)
    {
        ROS_ERROR_STREAM("Usage:  rosrun anrobot_description set_param arg" << "\n"
		         << "arg:  0 for simple, 1 for kdl");
        return 1;
    }
//http://wiki.ros.org/roscpp/Overview/NodeHandles
    ros::NodeHandle n;

    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    ros::ServiceClient kdl_client = n.serviceClient<lab03::kinematics>("kdl");
    ros::ServiceClient simple_client = n.serviceClient<lab03::kinematics>("simple");

    KinStruct k;
    k.use_kdl = atoi(argv[1]);
    k.marker_pub = &marker_pub;
    k.kdl_client = &kdl_client;
    k.simple_client = &simple_client;
    
    ros::Subscriber get_joint_states = n.subscribe<sensor_msgs::JointState>("joint_states", 100, boost::bind(joint_states_cb, _1, k));
    
    ros::spin();

    return 0;
}
