FLAGS = -Wall -std=c++17 -I header/
CLIBFLAG = -fPIC -shared
ILIBF = -L../lib/ -Wl,-rpath=../lib/ -lcaffparser
CC = g++

all: caffparser test

caffparser: parser.o
	mkdir -p ../lib ;\
	$(CC) $(FLAGS) $(CLIBFLAG) parser.o -o ../lib/libcaffparser.so

parser.o: src/parser.cpp
	$(CC) $(FLAGS) $(CLIBFLAG) -c src/parser.cpp -o parser.o

test: caffparser buildtest
	test/test.out

buildtest:
	$(CC) $(FLAGS) $(ILIBF) test/main.cpp -o test/test.out

clean:
	rm -f -v *.o *.so *.out ../lib/*.so test/*.out
