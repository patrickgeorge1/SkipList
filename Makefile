build:
	g++ main.cpp SkipList.cpp -o tema1
	./tema1

valgrind:
	g++ main.cpp SkipList.cpp -o tema1
	valgrind --leak-check=full -v ./tema1
