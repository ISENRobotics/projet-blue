#include <iostream>
#include <string>
#include "ros/ros.h"
#include <math.h>
#include <fstream>
#include <std_msgs/Float64.h>

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

float regul(position pos,float cap,objectif obj,float deltaMax);