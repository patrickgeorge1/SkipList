#include <iostream>
#include <string.h>
#include <sstream>
#include "SkipList.h"

using namespace std;
#define NMAX 5000


void solve(int &drivers, int &races, int &prints) {
	cout << "Drivers = 5 --   Races = 6 --  Prints = 2" << endl;
		//cout << " 3  1  0    and enter 12 23 34 " << endl;
	cin >> drivers >> races >> prints;
		int first_print = 1;

	int *laps = new int[drivers+1];                         // pt o mai usoara indexare de la 1
	int *laps_ant = new int[drivers+1]; 
	int *points = new int[drivers+1];
	int *car_from_points = new int[drivers+1];
	int *clasament_vechi = new int[drivers+1];

	for (int i = 1; i <= drivers; ++i)
	{
		clasament_vechi[i]  = 0;
	}


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


		if (!(input == "print"))  {

			time = std::stoi(input);
			if(time == 0) nulled++, time = 1001;
			Dictionary data(1, time);
			result.add(data);

			for (int j = 2; j <= drivers; ++j)
			{
				cin >> input;
				time = std::stoi(input);
				if(time == 0) nulled++, time = 1001;
				Dictionary dataOther(j, time);
				result.add(dataOther);
			}
			result.search(drivers, laps, laps_ant);




			points_received = (drivers - nulled)/2;
			for (int z = 1; z <= drivers - nulled; ++z)
			{

				if ((drivers - nulled)%2 == 0 && points_received == 0) points_received--;
				points[laps[z]] += points_received;
				points_received--;
			}
			for (int z = 1; z <= drivers; ++z)
			{
				//deltas[z] = laps[z] - laps_ant[z];
				

				laps_ant[z] = laps[z];
				car_from_points[z] = points[z];
			}

		}
		else
		{
    		int *display = new int[drivers+1];

    		for (int i = 1; i <= drivers; ++i)
    		{
    			display[i] = i;
    		}


			//cout << "Have to print!" << endl;
			for (int i = 1; i <= drivers; ++i)
			{
				int t = i;
				for (int j = i + 1; j <= drivers; ++j)
				{
					if (car_from_points[i] < car_from_points[j]) {
						int aux = car_from_points[j];
						int aux2 = display[i];
						display[i] = display[j];
						display[j] = aux2;
						car_from_points[j] = car_from_points[i];
						car_from_points[i] =aux; 
						t = j;
					} 
				}
			}

			if(first_print == 1)
			{
				for (int i = 1; i <= drivers; ++i)
				{
					cout << display[i] << " " << points[display[i]] <<" 0"<<endl;

				}
				for (int i = 1; i <= drivers; ++i)
				{
					clasament_vechi[display[i]] = i;

				}

				first_print = 0;
			}
			else
			{
				int clasament_nou[drivers+1];
				for (int i = 1; i <= drivers; ++i)                      // modific aici
				{
					clasament_nou[display[i]] = i;
				}

				for (int i = 1; i <= drivers; ++i)                      // modific aici
				{
					cout << display[i] << " " << points[display[i]] <<" "<<clasament_vechi[display[i]] - clasament_nou[display[i]]<<endl;

				}

				for (int i = 1; i <= drivers; ++i)                      // modific aici
				{
					clasament_vechi[display[i]] = i;
				}

			}



			delete[] display;
		}
		//cout << "x20..." << endl;
		//cout << "after destructor" << endl;
	}

	delete[] laps;
	delete[] laps_ant;
	delete[] points;
	delete[] clasament_vechi;
	delete[] car_from_points;
}