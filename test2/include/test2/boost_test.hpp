#include <ros/ros.h>
#include "std_msgs/String.h"
#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"
#include <boost/bind.hpp>

void perform(const std_msgs::String::ConstPtr& msg,std::string& param);