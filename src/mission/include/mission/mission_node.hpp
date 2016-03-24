#include <mission/mission.hpp>
#include <ros/ros.h>
#include <imu/YPR.h>
#include <nav_msgs/Odometry.h>
#include <regulateur/reg.h>
#include <boost/bind.hpp>



void refreshGPSPosition(const nav_msgs::Odometry& pos);
void refreshCap(const imu::YPR& data);
