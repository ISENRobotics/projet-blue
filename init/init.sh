#!/bin/bash -e

echo 'Debut de l initialisation...'

echo '[DTB] Listes des .dtbo chargees:'
dtbo=`cat /sys/devices/platform/bone_capemgr/slots`

echo $dtbo 
##############################################################
#pipe pour gpsd

echo "[GPSd] Initialisation de gpsd..."
gpsd /dev/ttyUSB0 -F /var/run/gpsd.sock
sleep 1
echo "[GPSd] Initialisation terminee"

##############################################################
#permet de connaitre les chip pwm utilisees

echo "[PWM] (chipsFinder.py) Ecriture des fichiers de cfg pwm  dans pwmcfg/..."
python3.4 chipsFinder.py 
sleep 2

ecapvar=`cat ./pwmcfg/ecap.cfg`
ehrpwmvar=`cat ./pwmcfg/ehrpwm.cfg`

##############################################################
#Installation du 1er pwm P9_14 PWMCHIP1/PWM0 SERVOMOTEUR

echo "[PWM] Initialisation du servomoteur : P9_14 @$ehrpwmvar/PWM0..."
echo 0 > "/sys/class/pwm/$ehrpwmvar/export"
sleep 1

echo 1 > "/sys/class/pwm/$ehrpwmvar/pwm0/enable"
sleep 1

echo 14000000 > "/sys/class/pwm/$ehrpwmvar/pwm0/period"
sleep 1

chmod 777 "/sys/class/pwm/$ehrpwmvar/pwm0/duty_cycle"
#############################################################
#Installation du 2eme pwm P9_16 PWMCHIP1/PWM0 MOTEUR.CC

echo "[PWM] Initialisation du moteur CC : P9_16 @$ehrpwmvar/PWM1..."
echo 1 > "/sys/class/pwm/$ehrpwmvar/export"
sleep 1

echo 1 > "/sys/class/pwm/$ehrpwmvar/pwm1/enable"
sleep 1

echo 14000000 > "/sys/class/pwm/$ehrpwmvar/pwm1/period"
sleep 1

chmod 777 "/sys/class/pwm/$ehrpwmvar/pwm1/duty_cycle"
#############################################################
#Installation du 3eme pwm P9_42 PWMCHIP0/PWM1 COMMANDE

echo "[PWM] Initialisation du pwm commande : P9_42 @$ecapvar/PWM0..."
echo 0 > "/sys/class/pwm/$ecapvar/export"
sleep 1

echo 1 > "/sys/class/pwm/$ecapvar/pwm0/enable"
sleep 1

echo 14000000 > "/sys/class/pwm/$ecapvar/pwm0/period"
sleep 1

chmod 777 "/sys/class/pwm/$ecapvar/pwm0/duty_cycle"
#############################################################

echo "[AHRS] Initialisation du razor..."
stty -F /dev/ttyO1 57600
sleep 2
echo "#o1" > /dev/ttyO1
sleep 1
echo "[AHRS] Initialisation du razor terminee !"
echo ''
echo 'Initialisation terminee'
