#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include "anrobot_description/PoseMessage.h"

float interpolate(float goal, float current, float time_delta)
{ //funkcja interpolująca
    float differance = goal - current;
    if (differance < -time_delta)
    {
        return current-time_delta;
    }
    else if(differance > time_delta)
    {
        return current+time_delta;
    }
    else
    {
        return goal;
    }
} 

void pose_callback (const anrobot_description::PoseMessageConstPtr &msg, geometry_msgs::PoseStamped &pose_state, ros::Publisher &pose_pub)
{
    ROS_INFO("Publisher positions: [%f %f %f %f]", msg->a,msg->b,msg->c, msg->d);
    ros::Rate loop_rate(50);
    pose_state.header.seq = 1;
    pose_state.header.stamp = ros::Time::now();
    pose_state.header.frame_id = "/base_link";
    pose_state.pose.position.x = interpolate(msg->a,pose_state.pose.position.x, msg->d);
    pose_state.pose.position.y = interpolate(msg->b,pose_state.pose.position.y, msg->d);
    pose_state.pose.position.z = interpolate(msg->c,pose_state.pose.position.z, msg->d);
    pose_state.pose.orientation.x = 1;
    pose_state.pose.orientation.y = 1;
    pose_state.pose.orientation.z = 1;
    pose_state.pose.orientation.w = 1;
    pose_pub.publish(pose_state);

    loop_rate.sleep();
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "pose_interpolator");
    ros::NodeHandle n;
    ros::Publisher pose_pub = n.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1);
     
    float initial_position[3];
    for (int i = 0; i<3; ++i)
    {
        initial_position[i] = 0;
    }
    geometry_msgs::PoseStamped pose_state;

    pose_state.header.seq = 1;
    pose_state.header.stamp = ros::Time::now();
    pose_state.header.frame_id = "/base_link";
    pose_state.pose.position.x = initial_position[0];
    pose_state.pose.position.y = initial_position[1];
    pose_state.pose.position.z = initial_position[2];
    pose_state.pose.orientation.x = 1;
    pose_state.pose.orientation.y = 1;
    pose_state.pose.orientation.z = 1;
    pose_state.pose.orientation.w = 1;
    pose_pub.publish(pose_state);

    ros::Subscriber sub = n.subscribe<anrobot_description::PoseMessage>("pose_topic",
                                                                             1000, 
                                                                             boost::bind(pose_callback, _1, pose_state, pose_pub));

    ros::spin();

    return 0;
}
