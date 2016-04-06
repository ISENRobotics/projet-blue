#include <selecteur/selecteur.hpp>

int main(int argc, char **argv)
{
  
	ros::init(argc, argv, "selecteur_node");

	Servo selecteur("selecteur");

	ros::NodeHandle n;

	//Creation du topic de selection
	ros::Publisher topicSelecteur = n.advertise<std_msgs::Float64>("commandeSel",1);

	//Inscription aux 3 topics de commande
	ros::Subscriber subSelecteur = n.subscribe("commandeSel", 1, &Servo::commande, &selecteur);

	//Declaration des variables
	ros::Rate loop_rate(10);
	std_msgs::Float64 cmd;
	bool init = false;

	while (ros::ok())
	 {
	 	if (init == false)
	 	{
	 		cmd.data = 1;
	 		topicSelecteur.publish(cmd);
	 		init = true;
	 	}

		
	    //rajouter pour le refresh
	    ros::spinOnce();

	    //sleep le temps de loop_rate
	    loop_rate.sleep();

	 }

	return 0;
}