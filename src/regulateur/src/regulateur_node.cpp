#include <regulateur/regulateur_node.hpp>


int main(int argc, char **argv)
{

  //Initialisation
    ros::init(argc, argv, "regulateur_node");

  //Declaration des variables
  ros::NodeHandle n;
  std_msgs::Float64 commande;
  regulateur::debugreg outReg;
  struct debugReg regout;
  Regulateur regulateur1;

  //Publish (direction & vitesse)
    ros::Publisher topicDirection = n.advertise<std_msgs::Float64>("commandeDir", 1);
    ros::Publisher topicDebugReg = n.advertise<regulateur::debugreg>("debugRegulateur",100);

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

    regulateur1.debug();

    regout = regulateur1.getRegParam();
    //publie aussi sur le topic de debug :
    outReg.gpspos0 = regout.gpspos0;
    outReg.gpspos1= regout.gpspos1;
    outReg.pos0= regout.pos0;
    outReg.pos1= regout.pos1;
    outReg.cap = regout.cap;
    outReg.obja0 = regout.obja0;
    outReg.obja1 = regout.obja1;
    outReg.objb0 = regout.objb0;
    outReg.objb1  = regout.objb1;
    outReg.deltaMax = regout.deltaMax;
    outReg.u0 = regout.u0;
    outReg.u1 = regout.u1;
    outReg.v0 = regout.v0;
    outReg.v1 = regout.v1;
    outReg.detUV = regout.detUV;
    outReg.phi = regout.phi;
    outReg.thetaD = regout.thetaD;
    outReg.diffTheta = regout.diffTheta;
    outReg.deltaD = regout.deltaD;

    topicDebugReg.publish(outReg);

    //rajouter pour le refresh
    ros::spinOnce();

    //sleep le temps de loop_rate
    loop_rate.sleep();

  }


  return 0;
}

