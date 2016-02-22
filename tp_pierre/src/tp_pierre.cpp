#include "../include/tp_pierre/tp_pierre.hpp"

/*
* node agissant sur le robot quand le bumper est enfonce
*
*/

//Declaration global
//ros::Publisher topicMvt;
//Fonction a appeler quand un message est reçu--------------------------------------------
void perform(const kobuki_msgs::BumperEvent::ConstPtr& msg)
{
	geometry_msgs::Twist cmd;
	cmd.angular.x = 0;
	cmd.angular.y = 0;
	cmd.angular.z = 5;

	cmd.linear.x = 0;
	cmd.linear.y = 0;
	cmd.linear.z = 0;
	ROS_INFO("Etat du bbumper : %d",msg->bumper);

	//Si le bumper est enfonce
	if (msg->bumper !=0)
	{
		topic.publish(cmd);
		ros::Duration(10).sleep(); // sleep pour X sec

		cmd.angular.z = 0;
		cmd.linear.x = 5;
		topic.publish(cmd);
		ros::Duration(10).sleep();
	}
	/*geometry_msgs::Twist cmd2;
	cmd2.angular.x = 0;
	cmd2.angular.y = 0;
	cmd2.angular.z = 5;

	cmd2.linear.x = 0;
	cmd2.linear.y = 0;
	cmd2.linear.z = 0;
	topicMvt.publish(cmd2);
	ROS_INFO("angular z= %f\n",cmd2.angular.z);
	ros::Duration(3).sleep(); // sleep pour X sec

	cmd2.angular.z = 0;
	cmd2.linear.x = 5;
	topicMvt.publish(cmd2);
	ROS_INFO("linear x= %f\n",cmd2.linear.x);
	ros::Duration(3).sleep(); // sleep pour X sec
	*/
}
//main
int main(int argc, char **argv)
{

  //Initialisation------------------------------------------------------------------------
  ros::init(argc, argv, "tp_pierre");

  //Declaration var-----------------------------------------------------------------------
  ros::NodeHandle n;
  geometry_msgs::Twist mvt;
  mvt.linear.x = 4;
  mvt.linear.y = 0;
  mvt.linear.z = 0;
  mvt.angular.x = 0;
  mvt.angular.y = 0;
  mvt.angular.z = 4;

  



  //TOPIC -------------------------------------------------------------------------------
  
  //inscription au topic de mouvement du turtlebot
 ros::Publisher topicMvt = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop",1000);          

  //publication au topic du bumper
  ros::Subscriber sub = n.subscribe<kobuki_msgs::BumperEvent>("/mobile_base/events/bumper",
  													  	 	  1000,
  													          perform;

  //Essaye de recuperer autant de message asap--------------------------------------------
  ros::spin();

  return 0;
}

