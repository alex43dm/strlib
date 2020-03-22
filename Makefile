
.PHONY: all

all: lib test

lib: main.o
	g++ -shared -o strlib.so main.o

main.o: main.cpp main.h
	g++ -c -g -Wall -Werror -std=c++11 -fpic main.cpp

test.o: test.cpp
	g++ -c -g -Wall -Werror -std=c++11 -DWITH_THREADS test.cpp

test: test.o main.o
	g++ -lgtest -pthread -o test test.o main.o
	./test

docker:
	docker build - < Dockerfile

clean:
	rm -rf *.o strlib.so test
