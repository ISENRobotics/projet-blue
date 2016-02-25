#include "../include/pwmServo/pwmServo.hpp"


//Servo servo(1,190000);
//Fonction a appeler quand un message est reçu
void performWhenNewCommande(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
  //servo.setDuty(110000);
}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "pwmServo");

  
  ros::NodeHandle n;

 //s'inscrit à un topic 
 //n.subscribe("nom_topic",taille,fonctionAAppeler)
  ros::Subscriber sub = n.subscribe("commandeServo", 1000,performWhenNewCommande);

  //Essaye de recuperer autant de message asap
  ros::spin();

  return 0;
}
