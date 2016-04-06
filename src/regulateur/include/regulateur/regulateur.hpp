#include <iostream>
#include <string>
#include "ros/ros.h"
#include <math.h>
#include <fstream>
#include <std_msgs/Float64.h>
#include <sensor_msgs/NavSatFix.h>
#include <regulateur/reg.h>
#include <regulateur/debugreg.h>

#define COULOIR 2


struct debugReg
{
	float gpspos0;
	float gpspos1;
	float pos0;
	float pos1;
	float cap;
	float obja0;
	float obja1;
	float objb0;
	float objb1 ;
	float deltaMax;
	float u0;
	float u1;
	float v0;
	float v1;
	float detUV;
	float phi;
	float thetaD;
	float diffTheta;
	float deltaD;
};

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
		int index;
		float u[2],v[2];
		float detUV;
		float phi;
		float diffTheta;


	public:
	//Fonction de callback ros
	Regulateur();
	void setRegulateurInput(const regulateur::reg& param);
	struct position getPosition();
	float getCap();
	struct objectif getObjectif();
	struct debugReg getRegParam();
	float getDeltaMax();
	float regul(position pos,float cap,objectif obj,float deltaMax);
	void debug();
	void getGPSPosition(const sensor_msgs::NavSatFix::ConstPtr& gpsData);

};
