#include <mission/mission.hpp>

//Constructeur
Mission::Mission(std::string path,float braquageMax)
{
	pos.x = 0;
	pos.y = 0;
	posInitiale.x = 0;
	posInitiale.y = 0;
	angleRoues = 0;
	cap = 0;
	deltaMax = braquageMax;
	cheminObjectif = path.c_str();
	objectifActuel = 0;
	this->objectifAtteint = false;


	//Determine le nombre d'objectif a atteindre
   	std::ifstream fichier(cheminObjectif, std::ios::in);
    while ( fichier.ignore( std::numeric_limits<int>::max(), '\n' ) )  
    {  
      ++nbresDeLignes;  
    } 

     // 3lignes sont utilise pour chaque objectif sauf le dernier objectif
     // qui n'utilise que 2 lignes
     nbresObjectifs = (nbresDeLignes+1)/3;  // si 11 lignes : (11+1)/3 = 4 objectifs

}

float Mission::getDeltaMax()
{
	return deltaMax;
}
//Recupere la position
void Mission::setPosition(const nav_msgs::Odometry::ConstPtr& posi)
{	
	pos.x = posi->pose.pose.position.x;
	pos.y = posi->pose.pose.position.y;

}

const struct position Mission::getPosition()
{
	return this->pos;
}


//Recupere le cap
void Mission::setCap(const imu::YPR::ConstPtr& data)
{
	  this->cap = data->Y;
}

float Mission::getCap()
{
	return this->cap;
}


//Recupere la latitude et la longitude de l'objectif a atteindre
void Mission::setObjectif(int objectifActuel)
{

	//Declaration des variables
	std::string buffer,zone;
	double northing,easting;
	objectif result;
	std::fstream fichier(cheminObjectif, std::ios::in);
	int numLigneObjectif = objectifActuel*3 +1 ;


	if (fichier)
	{
		//1ere position GPS : a
		goToLine(fichier,numLigneObjectif);
		fichier >> buffer;
		result.a[0] = std::stod(buffer);
		
		goToLine(fichier, numLigneObjectif+1);
		fichier >> buffer;
		result.a[1] = std::stod(buffer);

		gps_common::LLtoUTM(result.a[0], result.a[1], northing, easting, zone);
		result.a[0] = northing;
		result.a[1] = easting;
		

		//2eme position gps : b
		goToLine(fichier, numLigneObjectif+3);
		fichier >> buffer;
		result.b[0] = std::stod(buffer);

		
		goToLine(fichier, numLigneObjectif+4);	
		fichier >> buffer;
		result.b[1] = std::stod(buffer);

		gps_common::LLtoUTM(result.b[0], result.b[1], northing, easting, zone);
		result.b[0] = northing;
		result.b[1] = easting;
		
		fichier.close();

		this->obj = result;
	}
	else
	{
		result.a[0] = 0;
		result.a[1] = 0;
		result.b[0] = 0;
		result.b[1] = 0;
		std::cerr << "impossible d ouvrir le fichier (chemin:"<< cheminObjectif << ")" << std::endl;
	}

	}

objectif Mission::getObjectif()
{
	return obj;
}




//permet de se placer a une ligne precise d'un fichier txt
//voir : http://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
std::fstream& Mission::goToLine(std::fstream& file, unsigned int num)
{
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i)
    {
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

void Mission::debug()
{
	std::cout << "\n###debug() ---------------"
			  << "\n. posInitiale.x =" << posInitiale.x
			  << "\n. posInitiale.y =" << posInitiale.y
			  << "\n. nbresObjectifs =" << nbresObjectifs
			  << "\n--------------- debug()###" << std::endl;
}
//Destructeur
Mission::~Mission()
{

}
