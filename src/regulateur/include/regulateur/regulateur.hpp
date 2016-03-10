#include <iostream>
#include <string>
#include <ros/ros.h>
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
		std::vector< std::vector<float> > objectifs;
		int objectifActuel;
		int nbresObjectifs;
		std::ifstream fichier;
		int nbresDeLignes;




	public:
		Regulateur();
		float process(float a[2], float b[2]);
		void setPosition(const nav_msgs::Odometry& pos);
		void setTheta(const imu::YPR& data);
		void setObjectifs();
		void debug();
		~Regulateur();


};