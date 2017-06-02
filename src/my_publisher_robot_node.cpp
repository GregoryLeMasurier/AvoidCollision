#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

ros::Publisher pub;

void LaserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
//geometry_msgs::Twist twist_msg;
//pub.publish(twist_msg);
}

void TwistCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
pub.publish(msg);
}

int main(int argc, char* argv[]){

ros::init(argc, argv, "my_publisher_robot");

ros::NodeHandle n;

pub = n.advertise<geometry_msgs::Twist>("/Robot/cmd_vel",1000);

ros::Subscriber subTwist = n.subscribe("/cmd_vel", 1000, TwistCallback);
ros::Subscriber subLaser = n.subscribe("/base_scan", 1000, LaserCallback);

ros::spin();

return 0;

}

