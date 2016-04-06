#include <iostream>
#include <string>
#include <fstream>
#include <std_msgs/Float64.h>
#include <boost/bind.hpp>

#define DIR_PWM_MAX  1800000
#define DIR_PWM_MIN   980000
#define DIR_PWM_ZERO 1380000
#define DIR_K 		 1018591.6

#define MOT_PWM_MAX  1900000
#define MOT_PWM_MIN   800000
#define MOT_PWM_ZERO 1300000
#define MOT_K 		 	5500

#define SEL_PWM_MAX 	14000000
#define SEL_PWM_MIN 	   	   0
#define SEL_PWM_ZERO	 1200000
#define SEL_K			  800000




class Servo
{
	private:
		int duty;							//valeur du duty cycle
		int dutyMax;						//limite max du duty
		int dutyMin;						//limite min du duty
		std::string chip;					//nom du chip (pwmchip0/pwmchip1)
		std::string path;					//chemin absolu du pwm
		std::string type;
		float k; 							//coefficient 
		int zero;							//
		
		
	public:
		Servo();							//Constructeur
		//type = 'direction' ,'moteur', 'selecteur'
		Servo(std::string t_type);			//Constructeur 2
		void setDuty(int tmp);				//modifie le duty_cycle actuel	
		std::string getType();															
		std::string getChipEhr();			
		std::string getChipEcap();
		void commande(const std_msgs::Float64::ConstPtr& msg);
		void debug(const std_msgs::Float64::ConstPtr& msg);
		~Servo();							//destructeur


};
