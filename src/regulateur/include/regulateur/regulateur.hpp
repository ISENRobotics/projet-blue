#include <iostream>
#include <string>
#include "ros/ros.h"
#include <math.h>
#include <fstream>
#include <sensor_msgs/NavSatFix.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float64.h>
#include <imu/YPR.h>


#define COULOIR 5

struct objectif
{
	float a[2];
	float b[2];
};

class Regulateur
{
	private:
		
		float thetaD;			//cap voulu
		float position[2];		//position actuel de la voiture
		float theta;			//cap actuel de la voiture
		float deltaMax;			//angle max de braquage
		float deltaD;			//angle des roues






	public:
		static objectif obj;	//2 points donnant le segment à suivre
		void setObjectif(objectif tmpObj);
		Regulateur();
		float process();
		void setPosition(const nav_msgs::Odometry& pos);
		void setTheta(const imu::YPR& data);
		//void debug();
		~Regulateur();


};