#include "../include/pwmServo/pwmServo.hpp"


Servo pwmDir("direction");
Servo pwmMot("moteur");
Servo pwmSel("selecteur");



int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "Controleur_pwm");

  
  ros::NodeHandle n;

  //Inscription aux 3 topics de commande
  ros::Subscriber topicDir = n.subscribe("commandeDir", 1, &Servo::debug, &pwmDir);
  //ros::Subscriber sub = n.subscribe("commandeMot", 1, &Servo::commande, &pwmMot);
  //ros::Subscriber sub = n.subscribe("commandeSel", 1, &Servo::commande, &pwmSel);

  //Essaye de recuperer autant de message asap
  ros::spin();

  return 0;
}