#include "../include/pwmLib/pwmLib.h"


//CONSTRUCTEUR ///////////////////////////////////////////////////////////////////////////
Servo::Servo()
{
	duty = 75000;
}



Servo::Servo(std::string t_type,std::string t_chip)
{
	duty = 0;
	type = t_type;


	if(type =="direction")
	{
		dutyMax = DIR_PWM_MAX;
		dutyMin = DIR_PWM_MIN;

		chip = getChipEhr();
		path = "/sys/class/pwm/" + chip   +"/pwm0/duty_cycle";
	}

	else if (type=="moteur")
	{
		dutyMax = MOT_PWM_MAX;
		dutyMin = MOT_PWM_MIN;

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
		std::cout << "(methode setDuty) impossible d ecrire le duty" << std::endl;
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
void Servo::commande(int input)
{
	float buffer;
	if(type=="direction")
	{
		/* Si cest la direction input va de -180 a 180
		* on genere le pwm pour controler le servo
		* sans depasser les valeurs min & max */

		if(input < DIR_PWM_MAX && input > DIR_PWM_MIN)
		{
			buffer = input * DIR_K;
			duty = (int)buffer;
			setDuty(duty);

		}
		else
		{
			std::cout << "(Servo::commande) valeur limites depassees" << std::endl;
		}
	}

	else if(type=="moteur")
	{
		/*Si cest le moteur input va de -1 a 1
		*on genere le pwm pour controler le moteur
		* -1 : marche arr 100% , 0:arret, 1:marche avant 100%*/

		if(input < MOT_PWM_MAX && input > MOT_PWM_MAX)
		{
			buffer = input * MOT_K;
			duty = (int)buffer;
			setDuty(duty);
		}

	}

	else if(type=="selecteur")
	{
		/* Si cest le selecteur  input va de 1 a 2
		* on genere le pwm pour controler la carte
		* cytron ( 2: manette | 1: beaglebone) 
		* il faut generer un pwm < 1.5 ms pour que
		* la BB controle les pwm ou generer un signal = 0
		* ou > 1.5ms pour que l autre voie prenne le relais
		*/

		if(input == 1)
		{
			setDuty(1800000); //en ns 1800000 = 1.8ms
		}
		else if (input == 2)
		{
			setDuty(0);
		}
		else
		{
			std::cout << "(Servo::commande) erreur d input : 1 ou 2" << std::endl;
		}


	}

	else
	{
		std::cout << "(Servo::commande) : erreur de type !" << std::endl;
	}
}
//DESTRUCTEUR ///////////////////////////////////////////////////////////////////////////
Servo::~Servo()
{

}


