#!/bin/bash -e



## Script Bash lance au demarrage 
echo 'Debut de l initialisation...'


## Liste les fichiers dtb chargees
echo '[DTB] Listes des .dtbo chargees:'
dtbo=`cat /sys/devices/platform/bone_capemgr/slots`
echo $dtbo 



##Initialise  gpsd
echo "[GPSd] Initialisation de gpsd..."
gpsd /dev/ttyUSB0 -F /var/run/gpsd.sock
sleep 1
echo "[GPSd] Initialisation terminee"



##Au demarrage le chemin des pwms peut changer
##Voir (http://permalink.gmane.org/gmane.comp.hardware.beagleboard.user/86807)
echo "[PWM] Recherche des chemins des pwms..."
ls /sys/devices/platform/ocp/subsystem/devices/48302200.ehrpwm/pwm/ > pwmcfg/ehrpwm.cfg
ls /sys/devices/platform/ocp/subsystem/devices/48300100.ecap/pwm/ > pwmcfg/ecap.cfg
sleep 2

ecapvar=`cat ./pwmcfg/ecap.cfg`
ehrpwmvar=`cat ./pwmcfg/ehrpwm.cfg`


#Installation du 1er pwm P9_14 : direction
echo "[PWM] Initialisation du servomoteur : P9_14 @$ehrpwmvar/PWM0..."
echo 0 > "/sys/class/pwm/$ehrpwmvar/export"
sleep 1

echo 1 > "/sys/class/pwm/$ehrpwmvar/pwm0/enable"
sleep 1

##14 ms pour la periode de base des servomoteurs de la voiture
echo 14000000 > "/sys/class/pwm/$ehrpwmvar/pwm0/period"
sleep 1

chmod 777 "/sys/class/pwm/$ehrpwmvar/pwm0/duty_cycle"



#Installation du 2eme pwm P9_16 : moteur
echo "[PWM] Initialisation du moteur CC : P9_16 @$ehrpwmvar/PWM1..."
echo 1 > "/sys/class/pwm/$ehrpwmvar/export"
sleep 1

echo 1 > "/sys/class/pwm/$ehrpwmvar/pwm1/enable"
sleep 1

echo 14000000 > "/sys/class/pwm/$ehrpwmvar/pwm1/period"
sleep 1

chmod 777 "/sys/class/pwm/$ehrpwmvar/pwm1/duty_cycle"



#Installation du 3eme pwm P9_42 : selecteur
echo "[PWM] Initialisation du pwm commande : P9_42 @$ecapvar/PWM0..."
echo 0 > "/sys/class/pwm/$ecapvar/export"
sleep 1

echo 1 > "/sys/class/pwm/$ecapvar/pwm0/enable"
sleep 1

echo 14000000 > "/sys/class/pwm/$ecapvar/pwm0/period"
sleep 1

chmod 777 "/sys/class/pwm/$ecapvar/pwm0/duty_cycle"



##Initialisation du razor 9dof
echo "[AHRS] Initialisation du razor..."
stty -F /dev/ttyO1 57600     ##regle le baudrate a 57600
sleep 2
echo "#o1" > /dev/ttyO1      ##demande une reponse sous la forme (Yaw,Pitch,Roll)
sleep 1
echo "[AHRS] Initialisation du razor terminee !"
echo ''
echo 'Initialisation terminee'
