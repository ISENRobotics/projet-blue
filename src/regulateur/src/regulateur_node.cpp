#include <regulateur/regulateur.hpp>


//Instance du regulateur
Regulateur regulateur;


//fonction de callback ros pour la position
void refreshGPSPosition(const nav_msgs::Odometry& pos)
{
	regulateur.setPosition(pos);
}

//fonction de callback ros pour le cap
void refreshYPR(const imu::YPR& data)
{
	regulateur.setTheta(data);
}


int main(int argc, char **argv)
{

  //Initialisation


	//Declaration des variables
  ros::NodeHandle n;
  std_msgs::Float64 commande;
  std_msgs::Float64 commandeMot;

  //Publish (direction & vitesse)
  	ros::Publisher topicDirection = n.advertise<std_msgs::Float64>("commandeDir", 1);
    ros::Publisher topicMoteur = n.advertise<std_msgs::Float64>("commandeMot",1);

  //Subscribe (cap & position)
  	ros::Subscriber topicGPS = n.subscribe("odom",10,refreshGPSPosition);
  	ros::Subscriber topicIMU = n.subscribe("imu",1,refreshYPR);


  //frequence de calcul de l'asservissement
  ros::Rate loop_rate(10);


  //tant que le node n'a pas recu de signal kill
  while (ros::ok())
  {
  	//Calcule la commande de direction
  	commande.data = regulateur.process();
  	std::cout << "commande =" << commande.data << std::endl;

    //vitesse (-100 : 0 : +100)
    commandeMot.data = 30;

    //publie les message
    topicDirection.publish(commande);
    topicMoteur.publish(commandeMot);


    //rajouter pour le refresh
    ros::spinOnce();

    //sleep le temps de loop_rate
    loop_rate.sleep();

  }


  return 0;
}
