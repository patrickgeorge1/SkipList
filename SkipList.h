#include <iostream>
#include <ctime>

using namespace std;

struct Dictionary
{
	int time;
	int car_index;
	Dictionary(int car_index = -1, int time = -1) {
		this-> time = time;
		this-> car_index = car_index;
	}
};

struct Node{
	Dictionary data;
	Node *next;
	Node *prev;
	Node *up;
	Node *down;
	Node(Dictionary data) {
		next = nullptr;
		prev = nullptr;
		up = nullptr;
		down = nullptr;
		this->data = data; 
	} 	
};

class SkipList {
private:
	Node *head;
	Node *tail;
	int height;
	Node **address;
	int index_address;
	int drivers;

public:

	SkipList(int drivers) {
		this->drivers = drivers;
		height = 0;
		Dictionary data1(0, -1);
		Dictionary data2(0, 10001);
		head = new Node(data1);
		tail = new Node(data2);
		head->next = tail;
		tail->prev = head;
		address = new Node* [drivers * drivers];
		for (int i = 0; i < drivers * drivers; ++i)
		{
			address[i] = nullptr;
		}
		index_address = 0;
		address[0] = head;
		address[1] = tail;
		index_address += 2;
	}

	void remove_column(Node *botom) {
		Node *iterator = botom->up;;
		Node *save = iterator;
		while(iterator) {
			delete iterator->down;
			save = iterator;
			iterator = iterator->up;
		}
		delete save;

	}

	~SkipList() {
		// Node *now_head = head;    // cu asta oarcurg pe vert
		// Node *bottom = head;
		// while (now_head != nullptr) {
		// 	bottom = now_head;
		// 	now_head = now_head->down;
		// }
		// bottom = bottom->next;
		// Node *last = bottom;
		// while(bottom != nullptr) {
		// 	remove_column(bottom->prev);
		// 	last = bottom;
		// 	bottom = bottom->next;
		// }
		// remove_column(last);
		// delete head;
		// delete tail;


		// Safe delete

		for (int i = 0; i < drivers * drivers; ++i)
		{
			delete address[i];
		}
		delete[] address;
	}
// fara trisat
	void search(int drivers, int laps[], int laps_ant[]) {
		int *times = new int[drivers+1];
		int *car_ind = new int[drivers+1];
		int i = 1;

		Node *now = head;
		for (int i = 1; i <= height; ++i)
		{
			now = now->down;
		}
		now = now->next;
		cout << endl;


		while(now->next != nullptr)          // dupa asta now va fi pe ult element
		{
			//cout << now->data.car_index <<" " <<now->data.time<< endl;
			times[i] = now->data.time;
			car_ind[i] = now->data.car_index;
			now = now->next;
			i++;
		}




		int x = times[1];
		laps[1] = car_ind[1];
		for (int i = 2; i <= drivers; ++i)
		{
			int y = times[i];
			if(y == x && x != 1001)     // au scos acc timp si sunt consecutive 
			{
				int car1 = 0;
				int car2 = 0;
				int num = 1;

				while (car1==0 && car2==0 && num <= drivers) {
					if(laps_ant[num] == car_ind[i]) car2 = 1, laps[i-1] = car_ind[i], laps[i] = car_ind[i-1]; // y
					if(laps_ant[num] == car_ind[i-1]) car1 = 1, laps[i-1] = car_ind[i-1], laps[i] = car_ind[i]; // x

					num++;
				}
			}
			else
			{
				laps[i] = car_ind[i];
			}

			x = y;
		}


		for (int i = 1; i <= drivers; ++i)
		{
			//cout << "zzzzz lap " << laps[i]<<endl;
			//cout << "zzzzz car " << car_ind[i] << " on time " << times[i]<<endl;
		}

		delete[] times;
		delete[] car_ind;
		//cout << now->data.time << endl;
	}

	void add_beetween(Dictionary data) {             // introduc timp si index, timpul in mod principal
		Node *added = new Node(data);
		added->next= tail;
		added->prev = tail->prev;
		tail->prev->next =added;
		tail->prev =added;
		address[index_address] = added;
		index_address++;
		
	}

void add(Dictionary data) {             
		Node *added = new Node(data);
		Node *up_left = head;
		if(height != 0)
		{
			//cout << "already one floor" << endl;
			Node *last = up_left;
			while(up_left != nullptr)
			{
				//cout <<endl << "entered once vertical" << endl;
				while(up_left->next->data.time < added->data.time)
				{
					//cout <<endl << "entered once orizontal" << endl;
					up_left = up_left->next;
				}
				last = up_left;

			//	cout << "inainte de ultima coborare" << endl;
				up_left = up_left->down;
			//	cout << "dupa ultima coborare" << endl;
			}
			//   trebuie sa inserez in dreapta nodului last
			address[index_address] = added;
			index_address++;
			added->next = last->next;
			added->prev = last;
			last->next->prev = added;
			last->next = added;

			// sa i fac etaje
			int i = 0;
			while(flip_coin() && i<=height)   // construiesc etaje
			{
				//cout << endl << "floor "<< i+1 << "for "<< added->data.time  <<endl;
				Node *floor = new Node(data);
				floor->down =added;
				added->up = floor;
				added = added->up;
				address[index_address] = added;
				index_address++;
				i++;

			}
			int number_of_links = i;
			int ok = 0;   // nu am construit un etaj extra
			if(height < i) {               // daca cumva fac un nivel in plus
				//cout << "setting margins for now floor of "<< added->data.time << endl;
				Dictionary data1(0, -1);
				Dictionary data2(0, 10001);
				Node *head_s = new Node(data1);
				Node *head_d = new Node(data2);
				address[index_address] = head_s;
				index_address++;
				address[index_address] = head_d;
				index_address++;
				head_s->down = head;
				head_s->next = added;
				added->prev = head_s;
				added->next = head_d;
				head_d->down = tail;
				head_d->prev = added;
				head = head_s;           // head si tail updatate
				tail = head_d;			// cel mai inalt floor este linkat
				ok = 1;                 // am construit un etaj extra
			}
			height = i;   // updatez inaltimea generala
			// linkez florul nou cu cele vechi
			Node *iterator_head = head;
			if(ok) {              // cobor la nivelul de la care trebuie sa incep linkarile
				number_of_links--;
				added = added->down;
				iterator_head = iterator_head->down;

			}
			else 
			{
				for (int i = 1; i <= height - number_of_links; ++i)
				{
					iterator_head = iterator_head->down;
				}
			}
			// pe added am pe cea mai inalta iar pe iterator_head, inceputul corespunzator
			for (int i = 1; i <= number_of_links; ++i)
			{
				// conectez
				Node *iterator_orizontal = iterator_head;
				while(iterator_orizontal->next->data.time < added->data.time)  // caut sa vad unde inserez
				{
					iterator_orizontal = iterator_orizontal->next;
				}
				//cout << added->data.time << " was inserted on line "<< i << " in stanga lui " << iterator_orizontal->data.time<<endl;
				added->next = iterator_orizontal->next;
				added->prev = iterator_orizontal;
				iterator_orizontal->next->prev = added;
				iterator_orizontal->next = added;


				// cobor
				iterator_head = iterator_head->down;
				added = added->down;
			}


		}
		else             // checked pune bine pe primul
		{
			while(up_left->next->data.time < added->data.time)
			{
				//cout <<endl << "entered once orizontal --" << endl;
				up_left = up_left->next;
			}
			up_left->next->prev = added;
			address[index_address] = added;
			index_address++;
			added->next = up_left->next;
			added->prev = up_left;
			up_left->next = added;
			int i = 0;
			while(flip_coin() && i<=height)
			{
				//cout << endl << "new floor" <<endl;
				Node *floor = new Node(data);
				floor->down =added;
				added->up = floor;
				added = added->up;
				address[index_address] = added;
				index_address++;
				i++;

			}
			if(height < i) {
				//cout << "setting margins for now floor" << endl;
				Dictionary data1(0, -1);
				Dictionary data2(0, 10001);
				Node *head_s = new Node(data1);
				Node *head_d = new Node(data2);
				address[index_address] = head_s;
				index_address++;
				address[index_address] = head_d;
				index_address++;
				head_s->down = head;
				head_s->next = added;
				added->prev = head_s;
				added->next = head_d;
				head_d->down = tail;
				head_d->prev = added;
				head = head_s;
				tail = head_d;

			}
			height = i;
			//cout << "numbers of floors except base = " << height<< endl;	
		}

		
	}

	int flip_coin() {
		srand((unsigned)time(0)); 
		int i = (rand()%2);
		//cout << i << endl;
		return i;
	}
};


void solve(int &drivers, int &races, int &prints);
// void print(int points[20001]) -- descrescator