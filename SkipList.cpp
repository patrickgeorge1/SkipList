#include <fstream>
#include <string.h>
#include <sstream>
#include "SkipList.h"

using namespace std;
#define NMAX 5000
struct Clasament {
	int car_points;
	int clasament_vechi;
	int index_masina;
};
ifstream f("races.in");
ofstream g("races.out");
void solve(int &drivers, int &races, int &prints) {
	f >> drivers >> races >> prints;
		int first_print = 1;




	Clasament clasament[drivers+1];           // asa voi stoca clasament de la ultimul print
	for (int i = 1; i <= drivers; ++i)
	{
		clasament[i].car_points = 0;
		clasament[i].clasament_vechi = 0;
		clasament[i].index_masina = i;
	}



	int *laps = new int[drivers+1];                         // pt o mai usoara indexare de la 1
	int *laps_ant = new int[drivers+1]; 



	for (int i = 1; i <= drivers; ++i)
	{
		laps[i] = 0;			// golit
		laps_ant[i] = i;        // prima data 
	}


	for (int i = 1; i <= races + prints ; ++i)
	{

		int points_received = drivers/2;
		int nulled = 0;
		

		SkipList result(drivers * drivers);
		int time;
		string input;

		f >> input;


		if (!(input == "print"))  {

			time = std::stoi(input);
			if(time == 0) nulled++, time = 1001;
			Dictionary data(1, time);
			result.add(data);

			for (int j = 2; j <= drivers; ++j)
			{
				f >> input;
				time = std::stoi(input);
				if(time == 0) nulled++, time = 1001;
				Dictionary dataOther(j, time);
				result.add(dataOther);
			}
			result.search(drivers, laps, laps_ant);   // in laps o sa am masinile ordonate dupa cum trebuie sa primeasca punctele
			points_received = (drivers - nulled)/2;
			for (int i = 1; i <= drivers-nulled; ++i)
			{
				if((drivers-nulled)%2 == 0 && points_received ==0) points_received--;
				clasament[laps[i]].car_points += points_received;
				points_received--;
			}
			// scriu noul laps_ant
			Clasament aux[drivers+1];                   // copiez totul intr un clasament aditional
    		for (int i = 1; i <= drivers; ++i)
    		{
    			aux[i] = clasament[i];
    		}
    		for (int i = 1; i <= drivers; ++i)              // ordonez clasamentul care sa pregateste sa fie afisat
    		{
    			for (int j = i + 1; j <= drivers; ++j)
    			{
    				if(aux[i].car_points < aux[j].car_points) {
    					Clasament swapper = aux[i];
    					aux[i] = aux[j];
    					aux[j] = swapper;
    				}
    				if(aux[i].car_points == aux[j].car_points) {
    					if (aux[i].index_masina > aux[j].index_masina) {
	    					Clasament swapper = aux[i];
	    					aux[i] = aux[j];
	    					aux[j] = swapper;
	    				}
    				}
    			}
    			laps_ant[i] = aux[i].index_masina;
    		}



		}
		else // a primit comanda print
		{
    		Clasament aux[drivers+1];                   // copiez totul intr un clasament aditional
    		for (int i = 1; i <= drivers; ++i)
    		{
    			aux[i] = clasament[i];
    		}

    		for (int i = 1; i <= drivers; ++i)              // ordonez clasamentul care sa pregateste sa fie afisat
    		{
    			for (int j = i + 1; j <= drivers; ++j)
    			{
    				if(aux[i].car_points < aux[j].car_points) {
    					Clasament swapper = aux[i];
    					aux[i] = aux[j];
    					aux[j] = swapper;
    				}
    				if(aux[i].car_points == aux[j].car_points) {
    					if (aux[i].index_masina > aux[j].index_masina) {
	    					Clasament swapper = aux[i];
	    					aux[i] = aux[j];
	    					aux[j] = swapper;
	    				}
    				}
    			}
    		}




    		if (first_print == 1) {
				for (int i = 1; i <= drivers; ++i)
				{
					g << aux[i].index_masina << " " << aux[i].car_points << " 0"<<endl;
					clasament[aux[i].index_masina].clasament_vechi = i;
				}

    			first_print = 0;
    		}
    		else
    		{
    			for (int i = 1; i <= drivers; ++i)
    			{
    				g << aux[i].index_masina << " " << aux[i].car_points << " " << aux[i].clasament_vechi - i << endl;
    				clasament[aux[i].index_masina].clasament_vechi = i;
    			}
    		}
    		g << endl;
		}


	}
	g << endl;
	delete[] laps;
	delete[] laps_ant;
	f.close();
	g.close();
}