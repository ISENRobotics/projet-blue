#include "../include/ahrs/ahrs.hpp"



//Constructeur ---------------------------------------------------

//Constructeur par defaut
Ahrs::Ahrs()
{

	path = "/dev/ttyO1";
	yaw = 0;
	pitch = 0;
	roll = 0;


}


//Constructeur surcharge
Ahrs::Ahrs(std::string t_path)
{
	ROS_INFO("[ahrs.node] Initialisation du AHRS....\n");
	path = t_path;
	yaw = 0;
	pitch = 0;
	roll = 0;

	//Initialise le baudrate a 57600 pour le 9dof
	system("stty -F /dev/ttyO1 57600");
	ROS_INFO("[ahrs.node] Initialisation terminee\n")
}


//Accesseur ------------------------------------------------------
float Ahrs::getYaw()
{
	return this.yaw;
}

float Ahrs::getPitch()
{
	return this.pitch;
}

float Ahrs::getRoll()
{
	return this.roll;
}

//Fonction recuperant les donnees du razor 9dof -----------------
ahrsData getRawData()
{

}