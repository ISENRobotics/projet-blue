# projet-blue
voiture autonome team blue

§Description--------------------------------------
dépot contenant les différentes sources utilisées pour transformer une voiture RC en voiture autonome

§hardware-----------------------------------------
BeagleBone Black
razor 9dof
....
sbleuarg..

§Contenu------------------------------------------
init/
  dossier contenant le script d'initialisation pour la beaglebone
  il effectue les opérations suivantes:
    - initialise gpsd
    - initialise les pwm (P9_14/P9_16/P9_42)
    - initialise le AHRS razor
    
    
src/
  dossier issu d'un catkin workspace contenant les différents packages utilisées:
  
    ahrs/     -> package chargé de récupérer les infos du AHRS (sourcek: https://github.com/ptrbrtz/razor-9dof-ahrs)
    pwmLib/   -> librairie utilisé par le pak pwmServo afin de générer des signaux pwm
    pwmServo/ -> pak contenant le noeud de gestion des pwm
    gps_umd/  -> pak chargé de récupérer les données du gps (source: https://github.com/ktossell/gps_umd)
    
    
