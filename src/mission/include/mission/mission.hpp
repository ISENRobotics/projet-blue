#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits>
#include "ros/ros.h"
#include <nav_msgs/Odometry.h>
#include <imu/YPR.h>
#include <mission/conversions.h>
#include <std_msgs/Float64.h>

#define COULOIR 2

struct position
{
	float x;
	float y;
};
//Structure représentant un objectif (une droite)
struct objectif
{
	double a[2];		//lat & long du point a
	double b[2];
};


class Mission
{

	private:
		struct position pos;			//position actuelle de la voiture (odom)
		float angleRoues;				//angle des roues actuelles	(rad)
		float cap ;						//cap actuelle (rad)
		float deltaMax; 				//braquage des roues max
		struct objectif obj;	//position de l'objectif
		std::string cheminObjectif;		//chemin du fichier objectif
		

	public:
		int nbresObjectifs;				//nbres d'objectif  à atteindre
		int objectifActuel;				//numero de l'objectif actuel
		struct position posInitiale;		//position initiale de la voiture(odom)
		bool objectifAtteint;			//1 si on est sur l'objectif
		//vars utilisés pour l'initiallisation
		int nbresDeLignes;		

		//Constructeur  : -chemin : chemin du fichier objectifs)
		//				  -braquageMax : angles des roues max	
		Mission(std::string path,float braquageMax);

		//recupere la position actuelle de la voiture
		void setPosition(const nav_msgs::Odometry::ConstPtr& posi);
		const struct  position getPosition();

		//recupere le cap actuelle
		void setCap(const imu::YPR::ConstPtr& data);
		float getCap();

		//Recupere la position GPS de l'objectif actuel
		void setObjectif(int objectifActuel);
		objectif getObjectif();

		//recupere le deltaMax
		float getDeltaMax();

		//debug
		void debug();

		//destructeur
		~Mission();

		// --- fonctions pour l'initialisation
		//http://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
		std::fstream& goToLine(std::fstream& file, unsigned int num);
};