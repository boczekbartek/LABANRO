#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <std_msgs/String.h>
typedef struct kinematicsManagmentStruct
{
    bool use_kdl;
} KinStruct;


// float interpolate(float goal, float current, float time_delta){
//     float differance = goal - current;
//     if (differance < -time_delta){
//     	return current-time_delta;
//     }else if(differance > time_delta){
//     	return current+time_delta;
//     }else{
//     	return goal;
//     }
// } 

void chatterCallback(const sensor_msgs::JointStateConstPtr &msg, sensor_msgs::JointState &joint_state,const ros::Publisher &joint_pub)
{
  ros::Rate loop_rate(30);
  ROS_INFO("I heard: [%f]", msg->position[0]);
  
  joint_state.name[0] ="joint1";
  joint_state.position[0] = 2;
  joint_state.name[1] ="joint2";
  joint_state.position[1] = 1;
  joint_state.name[2] ="joint3";
  joint_state.position[2] = -1;
  //TODO
   joint_pub.publish(joint_state);
   loop_rate.sleep();
  //tutaj będzie wywołanie fukcji interpolate
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "aaastate_publisher");
    ros::NodeHandle n;
    ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
    // tf::TransformBroadcaster broadcaster;
    // ros::Rate loop_rate(30);
    sensor_msgs::JointState joint_state;
    joint_state.header.stamp = ros::Time::now();
    joint_state.name.resize(3);
    joint_state.position.resize(3);
    joint_state.velocity.resize(3);
    ros::Subscriber sub = n.subscribe<sensor_msgs::JointState>("joint_states", 1000, 
                                                               boost::bind(chatterCallback,_1,joint_state,joint_pub)); //tutaj trzea zrobic boost::bind zeby dac jako argumant fukcji chattercallback
    
    std::cout << joint_state.position[0] <<std::endl;
    // joint_pub.publish(joint_state);


    ros::spin();









//     const double degree = M_PI/180;

//     // robot state
//     double tilt = 0, tinc = degree, swivel=0, angle=0, height=0, hinc=0.005;

//     // message declarations
//     geometry_msgs::TransformStamped odom_trans;
//     sensor_msgs::JointState joint_state;
//     odom_trans.header.frame_id = "odom";
//     odom_trans.child_frame_id = "base_link";

//     while (ros::ok()) {
//         //update joint_state
//         joint_state.header.stamp = ros::Time::now();
//         joint_state.name.resize(3);
//         joint_state.position.resize(3);
//         joint_state.velocity.resize(3);
//         joint_state.name[0] ="joint1";
//         joint_state.position[0] = swivel;
//         joint_state.name[1] ="joint2";
//         joint_state.position[1] = tilt;
//         joint_state.name[2] ="joint3";
//         joint_state.position[2] = height;


//         // update transform
//         // (moving in a circle with radius=2)
//         odom_trans.header.stamp = ros::Time::now();
// //        odom_trans.transform.translation.x = cos(angle)*2;
// //        odom_trans.transform.translation.y = sin(angle)*2;
// //        odom_trans.transform.translation.z = .7;
//         //odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(angle+M_PI/2);
//         odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(angle+M_PI/2);

//         //send the joint state and transform
//         joint_pub.publish(joint_state);
//         broadcaster.sendTransform(odom_trans);

//         // Create new robot state


//         angle += degree/4;
//         if (!(swivel<-3.5 || swivel>1.6))
//             swivel = sin(angle)*3;
//         if (!(tilt<-0.93 || tilt>4))
//             tilt = sin (angle)*3;
//         height = cos (angle)*3;
//         // This will adjust as needed per iteration
//         loop_rate.sleep();
//     }


    return 0;
}
