#include "../include/regulateur/main.hpp"




Regulateur regulateur;

void refreshGPSPosition(const gps_common::GPSFix& pos)
{
	regulateur.setPosition(pos);
}

void refreshYPR(const imu::YPR& data)
{
	regulateur.setTheta(data);
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "regulateur");


	//Declaration des variables

  	ros::NodeHandle n;
  	std_msgs::Float64  commande;
    std_msgs::Float64 commandeMot;

  	float a[2],b[2];
  	a[0] = -60;
  	a[1] = -60;
  	b[0] = 60;
  	b[1] = 60;

  	//Publish
  	ros::Publisher topicDirection = n.advertise<std_msgs::Float64>("commandeDir", 1);
    ros::Publisher topicMoteur = n.advertise<std_msgs::Float64>("commandeMot",1);
  	//Subscribe
  	ros::Subscriber topicGPS = n.subscribe("fix",10,refreshGPSPosition);
  	ros::Subscriber topicIMU = n.subscribe("imu",1,refreshYPR);


  	//frequence de calcul de l'asservissement
  	ros::Rate loop_rate(10);


  //tant que le node n'a pas recu de signal kill
  while (ros::ok())
  {
  	//Calcule la commande
  	commande.data = regulateur.process(a,b);
  	std::cout << "commande =" << commande.data << std::endl;

    commandeMot.data = 30;

    //publie le message
    topicDirection.publish(commande);
    topicMoteur.publish(commandeMot);


    //rajouter pour le refresh
    ros::spinOnce();

    //sleep le temps de loop_rate
    loop_rate.sleep();

  }


  return 0;
}
