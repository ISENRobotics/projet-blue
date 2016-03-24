#include <regulateur/regulateur.hpp>


//Calcule l'angle des roues avant necessaire pour le suivi de ligne
float regul(position pos,float cap,objectif obj,float deltaMax)
{
  //Declaration des variables
  float a[2],b[2],vInst[2],u[2],v[2];
  float determinantUV,phi,thetaD,diffTheta,deltaD;
  float theta = cap;
  float posi[2];

  posi[0] = pos.x;
  posi[1] = pos.y;
  //assignation de l'objectif
  a[0] = obj.a[0];
  a[1] = obj.a[1];
  b[0] = obj.b[0];
  b[1] = obj.b[1];

  //Calcul du coeff directeur
  vInst[0] = b[0] - a[0];  //xb - xa
  vInst[1] = b[1] - a[1];  //yb -ya

  u[0] = vInst[0]/sqrt(pow(vInst[0],2)+pow(vInst[1],2));
  u[1] = vInst[1]/sqrt(pow(vInst[0],2)+pow(vInst[1],2));

  v[0] = posi[0] - a[0];
  v[1] = posi[1] - a[1];

  determinantUV = u[0]*v[1] - u[1]*v[0];

  phi = 2*atan(tan(atan2(vInst[1],vInst[0])/2));

  thetaD = phi - atan(determinantUV/COULOIR);

  diffTheta = 2*atan(tan((thetaD - theta)/2));
  deltaD = (deltaMax * diffTheta) / M_PI;

  return deltaD;
}


