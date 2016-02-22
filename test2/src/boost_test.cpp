#include "../include/test2/boost_test.hpp"




/*
*  node bumpernotification
*  s'inscrit au topic du bumper et sauvegarde le moment
*  ou le bumper est enfoncé
*  et publie sur un nouveau topic que le bumper est enfonce
*
*/

//Fonction a appeler quand un message est reçu--------------------------------------------
void perform(const std_msgs::String::ConstPtr& msg,std::string& param)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
  ROS_INFO("2nd parameters: [%s]",param.c_str());

}

//main
int main(int argc, char **argv)
{

  //Initialisation------------------------------------------------------------------------
  ros::init(argc, argv, "boost_test");

  //Declaration var-----------------------------------------------------------------------
  ros::NodeHandle n;
  std::string buff("COUCOU");							//var handle

  //Inscription au topic -----------------------------------------------------------------

  //FORMAT : ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  //topic de la commande du mouvement
   //topic du bumper
  ros::Subscriber sub = n.subscribe<std_msgs::String>("topicBind", 1000, boost::bind(&perform,_1,buff));


  


  //Essaye de recuperer autant de message asap--------------------------------------------
  ros::spin();

  return 0;
}


