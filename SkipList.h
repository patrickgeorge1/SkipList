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
	int width;
	// constructor + methods	
};


void solve(int &drivers, int &races, int &prints);
// void print(int points[20001]) -- descrescator
