#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

ros::Publisher pub;
sensor_msgs::LaserScan laser_msg;

void LaserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
laser_msg = *msg;
}

void JoystickCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
int size = ((laser_msg.angle_max - laser_msg.angle_min)/laser_msg.angle_increment) - 1;
int index = 0;
geometry_msgs::Twist twist_msgs;

twist_msgs = *msg;

for(index = (size/4); index < ((size*3)/4); index++){
if(laser_msg.ranges[index] < 0.3 && msg->linear.x > 0){
twist_msgs.linear.x = 0;
twist_msgs.angular.z = 0;
}
}

pub.publish(twist_msgs);
}

int main(int argc, char* argv[]){

ros::init(argc, argv, "my_publisher_robot");

ros::NodeHandle n;

pub = n.advertise<geometry_msgs::Twist>("/cmd_vel",1000);

ros::Subscriber subTwist = n.subscribe("/robot_joystick", 1000, JoystickCallback);
ros::Subscriber subLaser = n.subscribe("/base_scan", 1000, LaserCallback);

ros::spin();

return 0;

}

