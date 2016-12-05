#include <string>
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_broadcaster.h>
#include <std_msgs/String.h>

float interpolate(float goal, float current, float time_delta){ //funkcja interpolująca
  float differance = goal - current;
  if (differance < -time_delta){
   return current-time_delta;
 }else if(differance > time_delta){
   return current+time_delta;
 }else{
   return goal;
 }
} 

// void chatterCallback(const sensor_msgs::JointStateConstPtr &msg, sensor_msgs::JointState &joint_state,const ros::Publisher &joint_pub)
// {
//    ros::Rate loop_rate(50);
//   ROS_INFO("Positions from JSP: [%f %f %f]", msg->position[0],msg->position[1],msg->position[2]);
//   joint_state.header.stamp = ros::Time::now();
//   for (int i = 0; i<3; ++i)
//   {
//     //joint_state.position[i] = msg->position[i]+1;
//     joint_state.position[i] = interpolate(msg->position[i],joint_state.position[i],0.05);
//   }


//   ROS_INFO("Publisher positions: [%f %f %f]", joint_state.position[0],joint_state.position[1],joint_state.position[2]);

//    joint_pub.publish(joint_state);
//    loop_rate.sleep();
// }

int main(int argc, char** argv) {
  ros::init(argc, argv, "pose_interpolator");
  ros::NodeHandle n;
  ros::Publisher pose_pub = n.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1);
    // tf::TransformBroadcaster broadcaster;
    // ros::Rate loop_rate(30);
    float initial_position[3]; //tablica przechowue początkowe położewnia stawów
    for (int i = 0; i<3; ++i)
    { //inicjalizacja tablicy TODO docelowo zczytywanie z argsów
      initial_position[i] = atoi;
    }
    ros::Rate loop_rate(30);

    atoi(argv[2])
    geometry_msgs::PoseStamped pose_state;
    //inicjalizacja pozycjo jointów modelu 

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
    while(ros::ok){
      pose_state.header.seq = 1;
      pose_state.header.stamp = ros::Time::now();
      pose_state.header.frame_id = "/base_link";
      pose_state.pose.position.x = interpolate(pose_state.pose.position.x ,atoi(argv[3]),atoi(argv[2]));
      pose_state.pose.position.y = interpolate(pose_state.pose.position.y,,0.05);
      pose_state.pose.position.z = interpolate(pose_state.pose.position.z,argv[,0.05);
      pose_state.pose.orientation.x = 1;
      pose_state.pose.orientation.y = 1;
      pose_state.pose.orientation.z = 1;
      pose_state.pose.orientation.w = 1;
      pose_pub.publish(pose_state);
      loop_rate.sleep();

    }
    ros::spin();

    return 0;
  }
