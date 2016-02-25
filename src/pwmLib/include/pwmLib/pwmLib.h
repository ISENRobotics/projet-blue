#include <iostream>
#include <fstream>
#include <string>


//Valeur limites a ne pas depasser par les differents pwm
#define DIR_PWM_MAX 0
#define DIR_PWM_MIN 0
#define DIR_K 0

#define MOT_PWM_MAX 0
#define MOT_PWM_MIN 0
#define MOT_K 0

#define SEL_PWM_MAX 14000000
#define SEL_PWM_MIN 0




class Servo
{
	private:
		int duty;							//valeur du duty cycle
		int dutyMax;						//limite max du duty
		int dutyMin;						//limite min du duty
		std::string chip;					//nom du chip instancie (pwmchip0/pwmchip1)
		std::string path;					//chemin absolu du pwm
		std::string type;
		
 


	public:
		Servo();							//Constructeur
		//type = 'direction' ,'moteur', 'selecteur'
		Servo(std::string t_type,std::string t_chip);		//Constructeur 2
		void setDuty(int tmp);				//modifie le duty_cycle actuel	
		std::string getType();															
		std::string getChipEhr();			
		std::string getChipEcap();
		void commande(int input);
		~Servo();							//destructeur


};
