#include <iostream>
#include <string>
#include <ros/ros.h>
#include <math.h>
#include <gps_common/GPSFix.h>
#include <std_msgs/Float64.h>
#include <imu/YPR.h>


#define COULOIR 5


class Regulateur
{
	private:
		float position[2];
		float vInst[2];
		float theta;
		float deltaMax;
		float u[2], v[2];
		float determinantUV;		//Determinant de la matrice [u v]
		float phi;
		float thetaD;
		float diffTheta;
		float deltaD;




	public:
		Regulateur();
		float process(float a[2], float b[2]);
		void setPosition(const gps_common::GPSFix& pos);
		void setTheta(const imu::YPR& data);
		void setObjectifs();
		void debug();
		~Regulateur();


};