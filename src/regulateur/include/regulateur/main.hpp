#include <gps_common/GPSFix.h>
#include <imu/YPR.h>
#include <std_msgs/Int32.h>
#include "ros/ros.h"
#include <regulateur/regulateur.hpp>


void refreshGPSPosition(const gps_common::GPSFix& pos);
void refreshYPR(const imu::YPR& data);