#include <iostream>
#include <string.h>
#include <sstream>
#include "SkipList.h"

using namespace std;

#define NMAX 5000


void solve(int &drivers, int &races, int &prints) {
	cout << "Drivers  --   Races  --  Prints" << endl;
	cin >> drivers >> races >> prints;
	// vector cu lap-urile anterioare, initial 0
	// vector cu numar puncte fiecare masina
	for (int i = 0; i < races + prints + 1; ++i)
	{
		
		string input;
		std::getline (std::cin,input);
		if (!(input == "print"))  {
			 // cursa = inserez valori in lista

			// initializez lista  -- vezi sa nu se intample la fel ca atunci cand citea cu unul inainte
			istringstream is(input);    // transform string in stream de citit
			int time;
    		while( is >> time ) {
         		cout << time << endl;
         		// adaug element in lista
    		}
    		// parcurg lista si dau puncte in vector cu numar de puncte si vector "precedent"
    		// salvez in vector "precendent" lapurile astea
    		// clear list actuala
		}
		else {
    		// dau checkout sa vad clasament cu o functie
			cout << "Have to print!" << endl;
			// vector puncte descrescator
		}
	}
}