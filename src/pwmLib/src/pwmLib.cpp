#include "../include/pwmLib/pwmLib.h"


//CONSTRUCTEUR ///////////////////////////////////////////////////////////////////////////
Servo::Servo()
{
	duty = 75000;
}



Servo::Servo(std::string t_type)
{
	duty = 0;
	type = t_type;
	k = 0;


	if(type =="direction")
	{
		dutyMax = DIR_PWM_MAX;
		dutyMin = DIR_PWM_MIN;
		k = DIR_K;
		zero = DIR_PWM_ZERO;

		chip = getChipEhr();
		path = "/sys/class/pwm/" + chip   +"/pwm0/duty_cycle";
	}

	else if (type=="moteur")
	{
		dutyMax = MOT_PWM_MAX;
		dutyMin = MOT_PWM_MIN;
		k = MOT_K;
		zero = MOT_PWM_ZERO;

		chip = getChipEhr();
		path ="/sys/class/" + chip + "/pwm1/duty_cycle";
	}

	else if (type =="selecteur")
	{
		dutyMax = SEL_PWM_MAX;
		dutyMin = SEL_PWM_MIN;
		chip = getChipEcap();
		path ="/sys/class/pwm/" + chip + "/pwm0/duty_cycle";
	}

	else
	{
		std::cout << "[!]Erreur de type pour le pwm a genere !\n\ttypes:\n\t\tdirection\n\t\tmoteur\n\t\tcommande" << std::endl;
	}
}


//MODIFIE DUTY_CYCLE /////////////////////////////////////////////////////////////////////
void Servo::setDuty(int tmp)
{
	std::ofstream file(path.c_str(),std::ios::out | std::ios::trunc);
	if(file)
	{
		file << tmp;
		duty = tmp;
		file.close();
	}	
	else
	{
		std::cout << "(methode setDuty)["<< type <<"] impossible d ecrire le duty" << std::endl;
	}
}

//ACCESSEUR DU TYPE///////////////////////////////////////////////////////////////////
std::string Servo::getType()
{
	return type;
}

//RECUPERE LE CHIP////////////////////////////////////////////////////////////////////
std::string Servo::getChipEhr()
{
	std::string tmpChip;
	std::ifstream fichier("/home/ubuntu/init/pwmcfg/ehrpwm.cfg", std::ios::in);

	if (fichier)
	{
		getline(fichier,tmpChip);
		fichier.close();
	}
	else
	{
		std::cout << "impossible d ouvrir le fichier"<< std::endl;
	}

	return tmpChip;
}

//RECUPERE LE CHIP////////////////////////////////////////////////////////////////////
std::string Servo::getChipEcap()
{
	std::string tmpChip;
	std::ifstream fichier("/home/ubuntu/init/pwmcfg/ecap.cfg", std::ios::in);

	if (fichier)
	{
		getline(fichier,tmpChip);
		fichier.close();
	}
	else
	{
		std::cout << "impossible d ouvrir le fichier" << std::endl;
	}

	return tmpChip;
}


//COMMANDE PWM /////////////////////////////////////////////////////////////
void Servo::commande(const std_msgs::Float64& msg)
{


	float input = msg.data;
	float commandeNs = zero + input* k;

	if(type== "direction" || "moteur" || "selecteur")
	{


		if(commandeNs < dutyMax && commandeNs > dutyMin)
		{
			
			duty = (int)commandeNs;
			setDuty(duty);
			

		}
		else
		{
			std::cout << "(Servo::commande)["<< type <<"] valeur limites depassees" << std::endl;
		}
	}





	else
	{
		std::cout << "(Servo::commande) : erreur de type !" << std::endl;
	}
}


void Servo::debug(const std_msgs::Float64& msg)
{
	float input = msg.data;
	float commandeNs = zero + input* k;
	std::cout << "\n###debug() ---------------"
			  << "\n. type =" << type
			  << "\n. dutyMin =" << dutyMin
			  << "\n. dutyMax =" << dutyMax
			  << "\n. chip =" << chip
			  << "\n. path =" << path
			  << "\n. k =" << k
			  << "\n. zero =" << zero 
			  << "\n. commande =" << commandeNs
			  << "\n--------------- debug()###" << std::endl;
}
//DESTRUCTEUR ///////////////////////////////////////////////////////////////////////////
Servo::~Servo()
{

}
