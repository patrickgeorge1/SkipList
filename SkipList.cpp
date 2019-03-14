#include <iostream>
#include <string.h>
#include <sstream>
#include "SkipList.h"

using namespace std;
#define NMAX 5000


void solve(int &drivers, int &races, int &prints) {
	cout << "Drivers = 3 --   Races = 1 --  Prints = 0" << endl;
		//cout << " 3  1  0    and enter 12 23 34 " << endl;
	//cin >> drivers >> races >> prints;
		drivers = 3;
		races = 1;
		prints = 0;

	int *laps = new int[drivers+1];                         // pt o mai usoara indexare de la 1
	int *laps_ant = new int[drivers+1]; 
	int *points = new int[drivers+1];




	for (int i = 0; i < drivers+1; ++i)
	{
		laps[i] = 0;			// golit
		laps_ant[i] = i;           // o prostie random
		points[i] = 0;			// inca necompletate
	}

	for (int i = 1; i <= races + prints ; ++i)
	{

		int points_received = drivers/2;
		int nulled = 0;
		

		SkipList result(drivers * drivers);
		int time;
		string input;

		cin >> input;
		time = std::stoi(input);
		if(time == 0) nulled++, time = 1001;
		Dictionary data(1, time);
		result.add(data);

		if (!(input == "print"))  {
			for (int j = 2; j <= drivers; ++j)
			{
				cin >> input;
				time = std::stoi(input);
				if(time == 0) nulled++, time = 1001;
				Dictionary dataOther(j, time);
				result.add(dataOther);
			}
			result.search(drivers, laps, laps_ant);



			for (int z = 1; z <= drivers - nulled; ++z)
			{
				points[laps[z]] += points_received;
				points_received--;
			}
			for (int z = 1; z <= drivers; ++z)
			{
				laps_ant[z] = laps[z];
				cout << "@@ masina  " << z << " a obtinut " << points[z] << endl; 
			}

		}
		else
		{
    		// dau checkout sa vad clasament cu o functie
			cout << "Have to print!" << endl;
			// vector puncte descrescator
		}
		//cout << "x20..." << endl;
		cout << "after destructor" << endl;
	}

	delete[] laps;
	delete[] laps_ant;
	delete[] points;
}