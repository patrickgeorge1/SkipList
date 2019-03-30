buildd:
	g++ main.cpp -std=gnu++0x SkipList.cpp -o tema1
	./tema1
build:
	g++ main.cpp -std=gnu++0x SkipList.cpp -o tema1

dif:
	diff races.out ref/test6.out

valgrind:
	g++ main.cpp SkipList.cpp -o tema1
	valgrind --leak-check=full ./tema1

fisier:
	g++ main.cpp SkipList.cpp > input.txt -o tema1
	./tema1

clean:
	rm tema1
