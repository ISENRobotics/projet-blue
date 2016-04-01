#include <iostream>
#include <string>
#include "ros/ros.h"
#include <math.h>
#include <fstream>
#include <std_msgs/Float64.h>
#include <sensor_msgs/NavSatFix.h>
#include <regulateur/reg.h>

#define COULOIR 2

struct position
{
	float x;
	float y;
};




struct objectif
{
	float a[2];
	float b[2];
};

class Regulateur
{
	private:
		position pos;
		position posGPS;
		float cap;
		objectif obj;
		float deltaMax;
		float thetaDes;
		float deltaDes;


	public:
	//Fonction de callback ros
	Regulateur();
	void setRegulateurInput(const regulateur::reg& param);
	position getPosition();
	float getCap();
	objectif getObjectif();
	float getDeltaMax();
	float regul(position pos,float cap,objectif obj,float deltaMax);
	void debug();
	void getGPSPosition(const sensor_msgs::NavSatFix::ConstPtr& gpsData);

};
