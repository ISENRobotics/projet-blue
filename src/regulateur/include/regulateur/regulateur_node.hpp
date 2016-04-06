#include <std_msgs/Float64.h>
#include "ros/ros.h"
#include <regulateur/regulateur.hpp>


//Structure représentant les différents paramètres à envoyer à la fct regulateur
struct regInput
{
	position pos;
	float cap;
	objectif obj;
	float deltaMax;
};

