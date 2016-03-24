#include <regulateur/regulateur_node.hpp>

regInput inReg;

//position gps
void getRegulateurInput(const regulateur::reg& param)
{
  inReg.pos.x = param.pos0;
  inReg.pos.y = param.pos1;
  inReg.cap = param.cap;
  inReg.obj.a[0] = param.obja0;
  inReg.obj.a[1] = param.obja1;
  inReg.obj.b[0] = param.objb0;
  inReg.obj.b[1]= param.objb1;
  inReg.deltaMax = param.deltaMax;
}

int main(int argc, char **argv)
{

  //Initialisation


  //Declaration des variables
  ros::NodeHandle n;
  std_msgs::Float64 commande;

  //Publish (direction & vitesse)
    ros::Publisher topicDirection = n.advertise<std_msgs::Float64>("commandeDir", 1);
    

  //Subscribe (topic du regulateur)
    ros::Subscriber topicInput = n.subscribe("inputRegulateur",10,getRegulateurInput);



  //frequence de calcul de l'asservissement
  ros::Rate loop_rate(10);


  //tant que le node n'a pas recu de signal kill
  while (ros::ok())
  {
    //Calcule la commande de direction
    commande.data = regul(inReg.pos, inReg.cap, inReg.obj, inReg.deltaMax );
    std::cout << "commande =" << commande.data << std::endl;

    //publie les message
    topicDirection.publish(commande);

    //rajouter pour le refresh
    ros::spinOnce();

    //sleep le temps de loop_rate
    loop_rate.sleep();

  }


  return 0;
}