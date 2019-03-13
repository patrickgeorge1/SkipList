#include <iostream>
#include <string.h>
#include <sstream>
#include "SkipList.h"

using namespace std;

#define NMAX 5000


void solve(int &drivers, int &races, int &prints) {
	cout << "Drivers  --   Races  --  Prints" << endl;
		cout << " 3  1  0    and enter 12 23 34 " << endl;
	cin >> drivers >> races >> prints;
	int *laps = new int[drivers+1];                         // pt o mai usoara indexare de la 1
	int *points = new int[drivers+1];
	for (int i = 0; i < drivers+1; ++i)
	{
		laps[i] = 0;
		points[i] = 0;
	}

	for (int i = 1; i <= races + prints ; ++i)
	{
		
		SkipList result;
		int time;
		string input;
		cin >> input;
		time = std::stoi(input);
		Dictionary data(1, time);
		result.add_beetween(data);
		if (!(input == "print"))  {
			for (int j = 2; j <= drivers; ++j)
			{
				cin >> input;
				time = std::stoi(input);
				Dictionary dataOther(j, time);
				result.add_beetween(dataOther);
			}


			//test -- start
			int time_test;
			cout << "test a insert   ex 6,13" << endl;
			cin >> time_test; 
			Dictionary test(drivers+1, time_test);
			result.add(test);
			cout << "test when floors > 0 " << endl << "enter 13"<<endl;
			cin >> time_test;
			Dictionary test2(drivers+2, time_test);
			result.add(test2);

			cout << "test when floors > 1 " << endl << "enter 24"<<endl;
			cin >> time_test;
			Dictionary test3(drivers+3, time_test);
			result.add(test3);
			//test -- end



			result.search();
		}
		else
		{
    		// dau checkout sa vad clasament cu o functie
			cout << "Have to print!" << endl;
			// vector puncte descrescator
		}
		//cout << "x20..." << endl;
	}

	delete[] laps;
	delete[] points;
}
