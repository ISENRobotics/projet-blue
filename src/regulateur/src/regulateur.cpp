#include "../include/regulateur/regulateur.hpp"

Regulateur::Regulateur()
{
    position[0] = -70;
    position[1] = -80;
    vInst[1] = 0;
    vInst[0] = 0;
    theta = 0;
    deltaMax = M_PI/8;
    u[0] = 0;
    u[1] = 0;
    v[0] = 0;
    v[1] = 0;
    determinantUV = 0;    //Determinant de la matrice [u v]
    phi = 0;
    thetaD = 0;
    diffTheta = 0;
    deltaD = 0;
    objectifActuel = 1;
    nbresObjectifs = 0;

    //Determine le nombre d'objectif a atteindre
    std::ifstream fichier("/home/rosuser/objectif.txt", std::ios::in);
    int nbresDelignes;
    while ( fichier.ignore( std::numeric_limits<int>::max(), '\n' ) )  
    {  
      ++nbresDeLignes;  
    } 

      // 3lignes sont utilise pour chaque objectif sauf le dernier objectif
      // qui n'utilise que 2 lignes
      nbresObjectifs = (nbresDeLignes+1)/3;  // si 11 lignes : 11+1/3 = 4 objectifs
}

float Regulateur::process(float a[2], float b[2])
{
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

void Regulateur::setPosition(const nav_msgs::Odometry& pos)
{
  position[1] = -pos.pose.pose.position.x;
  position[0] = pos.pose.pose.position.y;

}

void Regulateur::setTheta(const imu::YPR& data)
{
  theta = data.Y;
}

/*
//Recupere la latitude et la longitude de l'objectif a atteindre
objectif Regulateur::setObjectifs()
{

  std::string gpsString;
  objectif balise;
  std::ifstream fichier("/home/ubuntu/objectif.txt", std::ios::in);
  int numLigneObjectif = (objectifActuel-1)*3 +1 ;
  int i = 0;
  if (fichier) 
  { 
    
  } 



  if (fichier)
  {
    iseof = getline(fichier,gpsString);
    if (iseof == eofbit)
      balises.a[0] = atof( gpsString.c_str() );
    getline(fichier,gpsString);
      balises.a[1] = atof( gpsString.c_str() );
    getline(fichier,gpsString);
    getline(fichier,gpsString);
      balises.b[0] = atof( gpsString.c_str() );
    getline(fichier,gpsString);
      balises.b[1] = atof( gpsString.c_str() );


    fichier.close();
  }
  else
  {
    std::cout << "impossible d ouvrir le fichier"<< std::endl;
  }

  return a;
*/
}

void Regulateur::debug()
{
  std::cout << "\n##debug() ------------\n"
            << ". position[0] =" << position[0]
            << "\t. position[1] =" << position[1]
            << "\n. vInst[0](vec) =" << vInst[0]
            << "\t. vInst[1](vec) =" << vInst[1]
            << "\n. theta = " << theta
            << "\n. deltaMax = " << deltaMax
            << "\n. u[0] =" << u[0]
            << "\t. u[1] =" << u[1]
            << "\n. v[0] =" << v[0]
            << "\t. v[1] =" << v[1]
            << "\n. determinantUV =" << determinantUV
            << "\n. phi =" << phi
            << "\n. thetaD =" << thetaD
            << "\n. diffTheta =" << diffTheta
            << "\n. deltaMax =" << deltaMax
            << "\n. deltaD = " << deltaD
            << "\n------------ debug()##\n" << std::endl;

}

Regulateur::~Regulateur()
{

}