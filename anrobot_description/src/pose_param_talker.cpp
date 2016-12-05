#include "ros/ros.h"
#include "anrobot_description/PoseMessage.h"
#include <cstdlib>
#include <iostream>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{

  ros::init(argc, argv, "pose_param_talker");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<anrobot_description::PoseMessage>("pose_topic", 1);

  ros::Rate loop_rate(50);


  float a = atof(argv[1]);
  float b = atof(argv[2]);
  float c = atof(argv[3]);
  float d = atof(argv[4]);


  anrobot_description::PoseMessage msg;
  while (ros::ok())
  {
    msg.a = a;
    msg.b = b;
    msg.c = c;
    msg.d = d;


      chatter_pub.publish(msg);

      

      loop_rate.sleep();
   
  }
  ros::spin();

  return 0;
}