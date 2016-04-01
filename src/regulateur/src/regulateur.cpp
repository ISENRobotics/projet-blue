#include <regulateur/regulateur.hpp>


Regulateur::Regulateur()
{
    pos.x = 0;
    pos.y = 0;
    cap = 0;
    obj.a[0] = 0;
    obj.a[1] = 0;
    obj.b[0] = 0;
    obj.b[1] = 0;
    deltaMax = 0;
    thetaDes = 0;
    deltaDes = 0;
}

//Calcule l'angle des roues avant necessaire pour le suivi de ligne
float Regulateur::regul(position pos,float cap,objectif obj,float deltaMax)
{
  //Declaration des variables
  float a[2],b[2],vInst[2],u[2],v[2];
  float determinantUV,phi,thetaD,diffTheta,deltaD;
  float theta = cap * M_PI / 180;
  float posi[2];

  posi[0] = pos.x;
  posi[1] = pos.y;
  //assignation de l'objectif
  a[0] = obj.a[0];
  a[1] = obj.a[1];
  b[0] = obj.b[0];
  b[1] = obj.b[1];

  //Calcul du coeff directeur
  vInst[0] = b[0] - a[0];  //xb -xa
  vInst[1] = b[1] - a[1];  //yb -ya

  u[0] = vInst[0]/sqrt(pow(vInst[0],2)+pow(vInst[1],2));
  u[1] = vInst[1]/sqrt(pow(vInst[0],2)+pow(vInst[1],2));

  v[0] = posi[0] - a[0];
  v[1] = posi[1] - a[1];

  determinantUV = u[0]*v[1] - u[1]*v[0];

  phi = atan2(vInst[1],vInst[0]);

  thetaD = phi - atan(determinantUV/COULOIR);
  this->thetaDes = thetaD;

  diffTheta = thetaD - theta;
  diffTheta = fmod((diffTheta + M_PI),(2*M_PI) ) - M_PI;
  deltaD = (deltaMax * diffTheta) / M_PI;

  this->deltaDes = deltaD;
  return deltaD;
}


//position gps
void  Regulateur::setRegulateurInput(const regulateur::reg& param)
{
  this->pos.x = param.pos0;
  this->pos.y = param.pos1;
  this->cap = param.cap;
  this->obj.a[0] = param.obja0;
  this->obj.a[1] = param.obja1;
  this->obj.b[0] = param.objb0;
  this->obj.b[1]= param.objb1;
  this->deltaMax = param.deltaMax;

  ROS_INFO("[regulateur] parametre recupere :\npos.x = %f\npos.y = %f\ncap = %f\nobj.a[0} = %f\nobj.a[1] = %f\nobj.b[0] = %f\nobj.b[1] = %f\n",this->pos.x,
                                                                                                                                               this->pos.y,
                                                                                                                                               this->cap,
                                                                                                                                               this->obj.a[0],
                                                                                                                                               this->obj.a[1],
                                                                                                                                               this->obj.b[0],
                                                                                                                                               this->obj.b[1]);
                                                                                                                                              
}

position Regulateur::getPosition()
{
  return this->pos;
}

float Regulateur::getCap()
{
  return this->cap;
}

objectif Regulateur::getObjectif()
{
  return this->obj;
}

float Regulateur::getDeltaMax()
{
  return this->deltaMax;
}

void Regulateur::getGPSPosition(const sensor_msgs::NavSatFix::ConstPtr& gpsData)
{
  this->posGPS.x = gpsData->latitude;
  this->posGPS.y = gpsData->longitude;
}

void Regulateur::debug()
{
  FILE * fp;

   fp = fopen ("/home/ubuntu/debug.txt", "w");
   fprintf(fp, "%10.10f,%10.10f,%10.10f,%10.10f,%10.10f,%10.10f,%10.10f,%10.10f,%10.10f,%10.10f,%10.10f\n",
                                                                                                               this->posGPS.x,
                                                                                                               this->posGPS.y,
                                                                                                               this->pos.x,
                                                                                                               this->pos.y,
                                                                                                               this->obj.a[0],
                                                                                                               this->obj.a[1],
                                                                                                               this->obj.b[0],
                                                                                                               this->obj.b[1],
                                                                                                               this->cap,
                                                                                                               this->thetaDes,
                                                                                                               this->deltaDes);
 
   
   fclose(fp);
}