#include <regulateur/regulateur.hpp>

//initialisation de membres statiques
objectif Regulateur::obj;


//Constructeur par defaut
Regulateur::Regulateur()
{
    position[0] = -70;
    position[1] = -80;
    theta = 0;
    deltaMax = M_PI/8;
    deltaD = 0;   

}

//Calcule l'angle des roues avant necessaire pour le suivi de ligne
float Regulateur::process()
{
  //Declaration des variables
  float a[2],b[2],vInst[2],u[2],v[2];
  float determinantUV,phi,thetaD,diffTheta;

  //assignation de l'objectif
  a[0] = Regulateur::obj.a[0];
  a[1] = Regulateur::obj.a[1];
  b[0] = Regulateur::obj.b[0];
  b[1] = Regulateur::obj.b[1];

  //Calcul du coeff directeur
  vInst[0] = b[0] - a[0];  //xb - xa
  vInst[1] = b[1] - a[1];  //yb -ya

  u[0] = vInst[0]/sqrt(pow(vInst[0],2)+pow(vInst[1],2));
  u[1] = vInst[1]/sqrt(pow(vInst[0],2)+pow(vInst[1],2));

  v[0] = position[0] - a[0];
  v[1] = position[1] - a[1];

  determinantUV = u[0]*v[1] - u[1]*v[0];

  phi = 2*atan(tan(atan2(vInst[1],vInst[0])/2));

  thetaD = phi - atan(determinantUV/COULOIR);

  diffTheta = 2*atan(tan((thetaD - theta)/2));
  deltaD = (deltaMax * diffTheta) / M_PI;

  return deltaD;
}


//Recupere la position actuelle
void Regulateur::setPosition(const nav_msgs::Odometry& pos)
{
  position[1] = -pos.pose.pose.position.x;
  position[0] = pos.pose.pose.position.y;

}


//Recupere le cap actuelle
void Regulateur::setTheta(const imu::YPR& data)
{
  theta = data.Y;
}

//Recupere l'objectif actuel
void Regulateur::setObjectif(objectif tmpObj)
{
  Regulateur::obj.a[0] = tmpObj.a[0];
  Regulateur::obj.a[1] = tmpObj.b[1];
  Regulateur::obj.b[0] = tmpObj.b[0];
  Regulateur::obj.b[1] = tmpObj.b[1];
}


Regulateur::~Regulateur()
{

}