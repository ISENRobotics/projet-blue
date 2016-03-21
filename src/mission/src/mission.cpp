#include <mission/mission.hpp>

//Constructeur
Mission::Mission()
{
	nbresObjectifs = 0;
	objectifActuel = 0;
	droite.a[0]  = 0;
}

Mission::Mission(std::string chemin)
{
	objectifActuel = 0;

	//Determine le nombre d'objectif a atteindre
   	std::ifstream fichier("/home/objectifs.txt", std::ios::in);
    while ( fichier.ignore( std::numeric_limits<int>::max(), '\n' ) )  
    {  
      ++nbresDeLignes;  
    } 

      // 3lignes sont utilise pour chaque objectif sauf le dernier objectif
      // qui n'utilise que 2 lignes
      nbresObjectifs = (nbresDeLignes+1)/3;  // si 11 lignes : (11+1)/3 = 4 objectifs
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

//Recupere la latitude et la longitude de l'objectif a atteindre
objectif Mission::setObjectif_droiteGPS(std::string chemin,int objectifActuel)
{

	//Declaration des variables
	std::string buffer;
	objectif result;
	std::fstream fichier(chemin.c_str(), std::ios::in);
	int numLigneObjectif = (objectifActuel-1)*3 +1 ;


	if (fichier)
	{
		//1ere position GPS : a
		goToLine(fichier, numLigneObjectif);
		std::getline(fichier, buffer);
		result.a[0] = std::stof(buffer);
		std::getline(fichier, buffer);
		result.a[1] = std::stof(buffer);

		//2eme position gps : b
		goToLine(fichier, numLigneObjectif+3);
		std::getline(fichier, buffer);
		result.b[0] = std::stof(buffer);
		std::getline(fichier, buffer);
		result.b[1] = std::stof(buffer);

		fichier.close();
	}
	else
	{
		result.a[0] = 0;
		result.a[1] = 0;
		result.b[0] = 0;
		result.b[1] = 0;
		std::cerr << "impossible d ouvrir le fichier (chemin:"<< chemin << ")" << std::endl;
	}

	return result;
	}
//Destructeur
Mission::~Mission()
{

}