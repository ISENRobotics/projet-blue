#include "../include/ahrs/RazorAHRS.h"
#include "ros/ros.h"
#include <iostream>   // cout()
#include <iomanip>    // setprecision() etc.
#include <stdexcept>  // runtime_error
#include <cstdio>     // getchar()



//port serie utilise
const string portSerie = "/dev/ttyO1";

//var globales pour recuperer les 3 valeurs
float globalYaw;
float globalPitch;
float globalRoll;



//Error callback function
void on_error(const string &msg)
{
	ROS_INFO("ERREUR: %s",msg);
}


//data callback function
void on_data(const float data[])
{
	//recupere les 3 valeurs
	globalYaw = data[0];
	globalPitch = data[1];
	globalRoll = data[2];
}



RazorAHRS *razor;
int main(int argc, char **argv)
{

  /*
   rajouter le nom en param "talker"
   */
  ros::init(argc, argv, "ahrs_node");


  ros::NodeHandle n;

  /*
   n.advertise<TYPE>("nom",nbre de msg)
   */
  ros::Publisher topicAHRS = n.advertise<ahrsData>("ahrsData", 1000);


  //rate de rafraichissement
  ros::Rate loop_rate(10);

  try
  {
  	razor = new RazorAHRS(portSerie,on_data,on_error,razorAHRS::YAW_PITCH_ROLL);
  }
  catch(runtime_error &e)
  {
    cout << "  " << (string("Could not create tracker: ") + string(e.what())) << endl;
    return 0;
  }


  //tant que le node n'a pas recu de signal kill
  while (ros::ok())
  {

    //Declaration du msg
    ahrsData msg;
    std::cout << "yaw=" << globalYaw << " pitch=" << globalPitch << " roll=" << globalRoll << std::endl;
    msg.yaw = globalYaw;
    msg.roll = globalRoll;
    msg.pitch = globalPitch;
    
    //publie le message
    topicAHRS.publish(msg);


    //rajouter pour le refresh
    ros::spinOnce();

    //sleep le temps de loop_rate
    loop_rate.sleep();
  }


  return 0;
}