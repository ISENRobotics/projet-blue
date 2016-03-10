#include <iostream>
#include <string>
#include <fstream>
#include <limits>

struct droiteGPS
{
	float a[2];		//lat & long du point a
	float b[2];
};


class Mission
{

	private:
		int nbresObjectifs;
		int objectifActuel;
		droiteGPS droite;



	public:
		mission();

		mission(std::string chemin,);

		//http://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
		std::fstream& goToLine(std::fstream& file, unsigned int num);

		//Recupere la position GPS de l'objectif actuel
		float[] setObjectif_droiteGPS(int objectifActuel);
		~mission();
}