build:
	g++ main.cpp SkipList.cpp -o tema1
	./tema1

valgrind:
	g++ main.cpp SkipList.cpp -o tema1
	valgrind --leak-check=full ./tema1

fisier:
	g++ main.cpp SkipList.cpp > input.txt -o tema1
	./tema1

clean:
	rm tema1
