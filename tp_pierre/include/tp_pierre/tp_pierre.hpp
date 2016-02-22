#include <iostream>
#include <string>
#include <ros/ros.h>
#include <boost/bind.hpp>

//header pour les formats des messages
#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"


void perform(const kobuki_msgs::BumperEvent::ConstPtr& msg,
			 ros::Publisher topic
			 );

