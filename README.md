# SkipList

https://ocw.cs.pub.ro/courses/sd-ca/teme/tema1


Intorducere

Piciorus este pasionat de curse de masini. El are o lista cu n concurenti pe care ii urmareste de-a lungul unui campionat format din m curse. Problema lui Piciorus este ca nu toti concurentii participa la toate cursele si ii este greu sa tina un clasament al acestora. Asa ca va cere voua ca din cand in cand sa afisati clasamentul rezultat in urma curselor desfasurate.
Desfasurarea campionatului
In campionat vor fi m curse. Datele despre o cursa vor fi date ca un sir de n numere: t_1, t_2, …, t_n, unde t_i este timpul pe care l-a avut concurentul cu id-ul i in acea cursa. 
Daca un concurent are t_i egal cu 0, asta inseamna ca el nu a participat la acea cursa (nici nu pierde, dar nici nu primeste puncte).
Fie P numarul de participanti ai unei curse. Acestia vor primi punctaje din intervalul [P/2, -P/2] in functie de pozitia pe care au ocupat-o in clasament astfel: primul (cel cu timpul minim, diferit de 0) va primi P/2 puncte, cel de pe locul al doilea va primi P/2 - 1 … penultimul -P/2 + 1, iar ultimul -P/2 puncte.
Inainte de inceperea campionatului participantii vor fi asezati in clasament in ordinea crescatoare a id-urilor.


Exemplu pentru o cursa.
n = 6
timpi cursa: 1 5 2 7 0 3
Rezolvare. P = 5, (numarul de participanti la cursa)
id = 1 primeste 2 puncte
id = 2 primeste -1 punct
id = 3 primeste 1 punct
id = 4 primeste -2 puncte
id = 5 primeste 0 puncte pentru ca nu a participat
id = 6 primeste 0 puncte.

//Daca P este par atunci niciun concurent nu va primi 0 puncte.


Exemplu

n = 5
1 4 2 3 0
P = 4
id = 1, primeste 2 puncte
id = 2, primeste -2 puncte
id = 3, primeste 1 puncte
id = 4, primeste -1 puncte
id = 5, primeste 0 puncte (pentru ca nu a participat)

//In cazul in care 2 concurenti au acelasi timp, vor fi departajati dupa pozitia ocupata in clasamentul anterior cursei actuale.


Operatii

Veti gasi in fisierul de intrare k operatii de tip “print”.
O operatie de tip print afiseaza clasamentul in ordinea descrescatoare a punctajelor.
Pentru fiecare competitor vor fi afisate 3 numere: ID-ul, Nr. de puncte acumulate de la inceputul campionatului si Diferenta de nivel din clasament fata de print-ul trecut.
Daca un competitor a urcat doua pozitii in clasament fata de print-ul trecut, Diferenta de nivel = 2, iar daca a coborat 3 pozitii, Diferenta de nivel = -3.


Cerinta

Creati un program care sa il ajute pe Piciorus sa isi urmareasca favoritii din campionatul descris mai sus.


Input

Pe prima linie se vor afla 3 numere n, m si k, reprezentand numarul de competitori, numarul de curse si numarul de print-uri.
Pe urmatoarele m + k linii se pot afla:
Sirul “print”.
n numere naturale separate printr-un spatiu, reprezentand timpul unui concurent intr-o cursa.
Citirea se va face din fisierul race.in

//Se garanteaza ca vor fi fix m curse si fix k print-uri.


Output

In fisierul de output se vor gasi n*(k + 1) linii (k clasamente, dupa fiecare clasament se va afisa o linie goala), fiecare linie continand 3 numere separate printr-un spatiu: ID-ul, Nr. de puncte acumulate de la inceputul campionatului si Diferenta de nivel din clasament fata de print-ul trecut.
Afisarea se va face in fisierul race.out

//Pentru primul print Diferenta de nivel va fi 0 pentru toti participantii.


Exemplu

in:
5 5 2
1 4 2 5 3
7 2 8 9 10
print
0 11 0 4 3
2 5 1 0 4
7 0 3 4 2
print

out:
primul print
1 3 0
2 1 0
3 1 0
5 -2 0
4 -3 0
al doilea print
3 4 2
1 2 -1
5 0 1
2 -2 -2
4 -4 0

Restrictii si precizari

Atenție! Structurile de date trebuie sa fie implementate generic.
0 < n < 1000
