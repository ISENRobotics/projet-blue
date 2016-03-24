#include <mission/mission_node.hpp>




// ---------------------------------------------------
// -------------- Main -------------------------------
// ---------------------------------------------------
int main(int argc, char **argv)
{

 	ros::init(argc, argv, "mission_node");
	//Instance de  mission
	Mission mission("/home/ubuntu/objectifs.txt",(M_PI/8));

  	//Declaration des variables
  	ros::NodeHandle n;

  regulateur::reg messageReg;
  std_msgs::Float64 messageMot;
  bool posInitialeRecup = false;


  //Publish
  	//pour le regulateur
  	ros::Publisher topicRegulateur = n.advertise<regulateur::reg>("inputRegulateur",1);
    ros::Publisher topicMot = n.advertise<std_msgs::Float64>("commandeMot",1);
  //Subscribe (cap & position)
  	ros::Subscriber topicGPS = n.subscribe("odom",10,&Mission::setPosition,&mission);
  	ros::Subscriber topicIMU = n.subscribe("imu",1,&Mission::setCap,&mission);

  //frequence de calcul de l'asservissement
  ros::Rate loop_rate(10);


	while (ros::ok())
	 {

	  	/*
	  		Debut de la mission
	  	*/

	  	//on stocke la position initiale de la voiture
	  	if (!posInitialeRecup)
	  	{
	  		position posIni = mission.getPosition();
	  		mission.positionInitiale[0] = posIni.x;
	  		mission.positionInitiale[1] = posIni.y;
	  		posInitialeRecup = true;	  		
	  	}

	  	mission.setObjectif(mission.objectifActuel);
	  	mission.objectifAtteint = false;

	  	//recupere l'objectif a atteindre
	  	//& preparation du message pour le topic regulateur
	  	objectif obj = mission.getObjectif();
	  	messageReg.obja0 = obj.a[0];
	  	messageReg.obja1 = obj.a[1];
	  	messageReg.objb0 = obj.b[0];
	  	messageReg.objb1 = obj.b[1];
	  	messageReg.deltaMax = mission.getDeltaMax();

	  	//Tant que l'objcetif n'est pas atteint
	  	while (!mission.objectifAtteint)
	  	{

	  		//pour la direction
		  	position pos = mission.getPosition();
		  	messageReg.pos0 = pos.x;
		  	messageReg.pos1 = pos.y;
		  	messageReg.cap = mission.getCap();

		  	//pour la vitesse
		  	messageMot.data = 30;

		  	//Publication sur les topis
		  	topicRegulateur.publish(messageReg);
		  	topicMot.publish(messageMot);

		  	//Si la voiture est dans le cercle de 2m autour de la balise b
		  	if ((pos.x >= (obj.b[0]-2)) && (pos.x <= (obj.b[0]+2)) )
		  	{
		  		if((pos.y >= (obj.b[1]-2)) && (pos.y <= (obj.b[1]+2)) )
		  		{
		  			mission.objectifAtteint = true;
		  			mission.objectifActuel++;

		  		}
		  	}

	  	}

	  	messageMot.data = 0;
	  	topicMot.publish(messageMot);


	    //rajouter pour le refresh
	    ros::spinOnce();

	    //sleep le temps de loop_rate
	    loop_rate.sleep();

	 }



  return 0;
}
