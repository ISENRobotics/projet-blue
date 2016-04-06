#include <regulateur/regulateur_node.hpp>


int main(int argc, char **argv)
{

  //Initialisation
    ros::init(argc, argv, "regulateur_node");

  //Declaration des variables
  ros::NodeHandle n;
  std_msgs::Float64 commande;
  Regulateur regulateur1;

  //Publish (direction & vitesse)
    ros::Publisher topicDirection = n.advertise<std_msgs::Float64>("commandeDir", 1);
    

  //Subscribe (topic du regulateur)
    ros::Subscriber topicInput = n.subscribe("inputRegulateur",10,&Regulateur::setRegulateurInput,&regulateur1);
    ros::Subscriber topicGPS = n.subscribe("fix",1,&Regulateur::getGPSPosition,&regulateur1);


  //frequence de calcul de l'asservissement
  ros::Rate loop_rate(10);


  //tant que le node n'a pas recu de signal kill
  while (ros::ok())
  {
    //Calcule la commande de direction
    commande.data = regulateur1.regul(regulateur1.getPosition(), regulateur1.getCap(), regulateur1.getObjectif(), regulateur1.getDeltaMax() );
    ROS_INFO("[regulateur_node] commande : %f",commande.data);

    //publie les message
    topicDirection.publish(commande);

    //rajouter pour le refresh
    ros::spinOnce();

    //sleep le temps de loop_rate
    loop_rate.sleep();

  }


  return 0;
}

