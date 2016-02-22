#include <iostream>
#include <string>
#include <ros/ros.h>
#include <stdlib.h>


//header pour les formats des messages


//Structure de base du ahrs
struct ahrsData
{
	float yaw;
	float pitch;
	float roll;
};


class Ahrs
{
	private:
		std::string path;		//Chemin  du ahrs
		float yaw;
		float pitch;
		float roll;


	public:
		Ahrs();
		Ahrs(std::string t_path);
		float getYaw();
		float getPitch();
		float getRoll();
		ahrsData getRawData();
		~Ahrs();



};


