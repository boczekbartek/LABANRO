#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
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

void chatterCallback(const sensor_msgs::JointStateConstPtr &msg, sensor_msgs::JointState &joint_state,const ros::Publisher &joint_pub)
{
 ros::Rate loop_rate(50);
 ROS_INFO("Positions from JSP: [%f %f %f]", msg->position[0],msg->position[1],msg->position[2]);
 joint_state.header.stamp = ros::Time::now();
 for (int i = 0; i<3; ++i)
 {
    //joint_state.position[i] = msg->position[i]+1;
  joint_state.position[i] = interpolate(msg->position[i],joint_state.position[i],0.05);
}


ROS_INFO("Publisher positions: [%f %f %f]", joint_state.position[0],joint_state.position[1],joint_state.position[2]);

joint_pub.publish(joint_state);
loop_rate.sleep();
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "interpolator");
  ros::NodeHandle n;
  ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("pozycje_jointow", 1);
    // tf::TransformBroadcaster broadcaster;
    // ros::Rate loop_rate(30);
  //ros::Publisher pose_pub = n.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1);

    float initial_position[3]; //tablica przechowue początkowe położewnia stawów
    for (int i = 0; i<3; ++i)
    { //inicjalizacja tablicy TODO docelowo zczytywanie z argsów
      initial_position[i] = 0;
    }

    sensor_msgs::JointState joint_state; 
    joint_state.header.stamp = ros::Time::now();
    joint_state.name.resize(3);
    joint_state.position.resize(3);
    joint_state.velocity.resize(3);
    joint_state.name[0] ="joint1";
    //inicjalizacja pozycjo jointów modelu 
    joint_state.position[0] = initial_position[0];
    joint_state.name[1] ="joint2";
    joint_state.position[1] = initial_position[1];
    joint_state.name[2] ="joint3";
    joint_state.position[2] = initial_position[2];
    joint_pub.publish(joint_state);

    ros::Subscriber sub = n.subscribe<sensor_msgs::JointState>("different_joint_states", 1000, 
                                                               boost::bind(chatterCallback,_1,joint_state,joint_pub)); //tutaj trzea zrobic boost::bind zeby dac jako argumant fukcji chattercallback


    ros::spin();

    return 0;
  }
