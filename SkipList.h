  // Copyright 2019 <Vitoga Geogege Patrick>
#ifndef _HOME_PATRICK_DESKTOP_SKIPLIST_FAC1_SKIPLIST_H_
#define _HOME_PATRICK_DESKTOP_SKIPLIST_FAC1_SKIPLIST_H_

#include <iostream>
#include <ctime>

struct Dictionary {
    int time;
    int car_index;
    explicit Dictionary(int car_index = -1, int time = -1) {
        this -> time = time;
        this -> car_index = car_index;
    }
};

struct Node {
    Dictionary data;
    Node * next;
    Node * prev;
    Node * up;
    Node * down;
    explicit Node(Dictionary data) {
        next = nullptr;
        prev = nullptr;
        up = nullptr;
        down = nullptr;
        this -> data = data;
    }
};

class SkipList {
 private:
    Node * head;
    Node * tail;
    int height;
    Node ** address;
    int index_address;
    int drivers;

 public:
        explicit SkipList(int drivers) {
            this -> drivers = drivers;
            height = 0;
            Dictionary data1(0, -1);
            Dictionary data2(0, 10001);
            head = new Node(data1);
            tail = new Node(data2);
            head -> next = tail;
            tail -> prev = head;
            address = new Node * [drivers * drivers];
            for (int i = 0; i < drivers * drivers; ++i) {
                address[i] = nullptr;
            }
            index_address = 0;
            address[0] = head;
            address[1] = tail;
            index_address += 2;
        }

    void swapp(int &a, int&b) {
        int aux = a;
        a = b;
        b = aux;
        b = aux;
    }

    void remove_column(Node * botom) {
            Node * iterator = botom -> up;;
            Node * save = iterator;
            while (iterator) {
                delete iterator -> down;
                save = iterator;
                iterator = iterator -> up;
            }
            delete save;
        }

        ~SkipList() {
              // Node *now_head = head;      // cu asta oarcurg pe vert
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

            for (int i = 0; i < drivers * drivers; ++i) {
                delete address[i];
            }
            delete[] address;
        }
      // fara trisat
    void search(int drivers, int laps[], int laps_ant[]) {
        int * times = new int[drivers + 1];
        int * car_ind = new int[drivers + 1];
        int i = 1;

        Node * now = head;
        for (int i = 1; i <= height; ++i) {
            now = now -> down;
        }
        now = now -> next;

        while (now -> next != nullptr)   // dupa asta now va fi pe ult element
        {
            // cout << now->data.car_index <<" " <<now->data.time<< std::endl;
            times[i] = now -> data.time;
            car_ind[i] = now -> data.car_index;
            now = now -> next;
            i++;
        }

        for (int i = 1; i <= drivers; ++i) {
            for (int j = i + 1; j <= drivers; ++j) {
                if (times[i] > times[j]) {
                    swapp(times[i], times[j]);
                    swapp(car_ind[i], car_ind[j]);
                }
                if (times[i] == times[j]) {
                    int oki = 0;
                    int okj = 0;
                    int p = 1;
                    while (oki == 0 && okj == 0 && p <= drivers) {
                        if (laps_ant[p] == car_ind[i]) oki = 1;
                        if (laps_ant[p] == car_ind[j]) okj = 1;
                        p++;
                    }
                    if (okj == 1) {
                        swapp(times[i], times[j]);
                        swapp(car_ind[i], car_ind[j]);
                    }
                }
            }
        }

        for (int i = 1; i <= drivers; ++i) {
            laps[i] = car_ind[i];
        }

        delete[] times;
        delete[] car_ind;
        // cout << now->data.time << std::endl;
    }

    void add_beetween(Dictionary data) {
    // introduc timp si index, timpul in mod principal
        Node * added = new Node(data);
        added -> next = tail;
        added -> prev = tail -> prev;
        tail -> prev -> next = added;
        tail -> prev = added;
        address[index_address] = added;
        index_address++;
    }

    void add(Dictionary data) {
        Node * added = new Node(data);
        Node * up_left = head;
        if (height != 0) {
            // cout << "already one floor" << std::endl;
            Node * last = up_left;
            while (up_left != nullptr) {
                // cout <<std::endl << "entered once vertical" << std::endl;
                while (up_left -> next -> data.time < added -> data.time) {
                    // cout <<std::endl << "entered
                    // once orizontal" << std::endl;
                    up_left = up_left -> next;
                }
                last = up_left;

                // cout << "inainte de ultima coborare" << std::endl;
                up_left = up_left -> down;
                // cout << "dupa ultima coborare" << std::endl;
            }
              //  trebuie sa inserez in dreapta nodului last
            address[index_address] = added;
            index_address++;
            added -> next = last -> next;
            added -> prev = last;
            last -> next -> prev = added;
            last -> next = added;

              // sa i fac etaje
            int i = 0;
            while (flip_coin() && i <= height)   // construiesc etaje
            {
                Node * floor = new Node(data);
                floor -> down = added;
                added -> up = floor;
                added = added -> up;
                address[index_address] = added;
                index_address++;
                i++;
            }
            int number_of_links = i;
            int ok = 0;   // nu am construit un etaj extra
            if (height < i) {   // daca cumva fac un nivel in plus
                Dictionary data1(0, -1);
                Dictionary data2(0, 10001);
                Node * head_s = new Node(data1);
                Node * head_d = new Node(data2);
                address[index_address] = head_s;
                index_address++;
                address[index_address] = head_d;
                index_address++;
                head_s -> down = head;
                head_s -> next = added;
                added -> prev = head_s;
                added -> next = head_d;
                head_d -> down = tail;
                head_d -> prev = added;
                head = head_s;   // head si tail updatate
                tail = head_d;   // cel mai inalt floor este linkat
                ok = 1;   // am construit un etaj extra
            }
            height = i;   // updatez inaltimea generala
              // linkez florul nou cu cele vechi
            Node * iterator_head = head;
            if (ok) {
            // cobor la nivelul de la care
            // trebuie sa incep linkarile
                number_of_links--;
                added = added -> down;
                iterator_head = iterator_head -> down;

            } else {
                for (int i = 1; i <= height - number_of_links; ++i) {
                    iterator_head = iterator_head -> down;
                }
            }
            // pe added am pe cea mai inalta
            // iar pe iterator_head, inceputul corespunzator
            for (int i = 1; i <= number_of_links; ++i) {
                  // conectez
                Node * iterator_orizontal = iterator_head;
                while (iterator_orizontal -> next -> data.time
                < added -> data.time)
                // caut sa vad unde inserez
                {
                    iterator_orizontal = iterator_orizontal -> next;
                }
                added -> next = iterator_orizontal -> next;
                added -> prev = iterator_orizontal;
                iterator_orizontal -> next -> prev = added;
                iterator_orizontal -> next = added;

                  // cobor
                iterator_head = iterator_head -> down;
                added = added -> down;
            }

        } else {   // checked pune bine pe primul
            while (up_left -> next -> data.time < added -> data.time) {
                up_left = up_left -> next;
            }
            up_left -> next -> prev = added;
            address[index_address] = added;
            index_address++;
            added -> next = up_left -> next;
            added -> prev = up_left;
            up_left -> next = added;
            int i = 0;
            while (flip_coin() && i <= height) {
                // cout << std::endl << "new floor" <<std::endl;
                Node * floor = new Node(data);
                floor -> down = added;
                added -> up = floor;
                added = added -> up;
                address[index_address] = added;
                index_address++;
                i++;
            }
            if (height < i) {
                // cout << "setting margins for now floor" << std::endl;
                Dictionary data1(0, -1);
                Dictionary data2(0, 10001);
                Node * head_s = new Node(data1);
                Node * head_d = new Node(data2);
                address[index_address] = head_s;
                index_address++;
                address[index_address] = head_d;
                index_address++;
                head_s -> down = head;
                head_s -> next = added;
                added -> prev = head_s;
                added -> next = head_d;
                head_d -> down = tail;
                head_d -> prev = added;
                head = head_s;
                tail = head_d;
            }
            height = i;
        }
    }

    int flip_coin() {
        srand((unsigned) time(0));
        unsigned int x = 13;
        unsigned int *seed = &x;
        int i = (rand_r(seed) % 2);
        // std::cout << i << std::endl;
        return i;
    }
};

void solve(int & drivers, int & races, int & prints);
#endif  // _HOME_PATRICK_DESKTOP_SKIPLIST_FAC1_SKIPLIST_H_
