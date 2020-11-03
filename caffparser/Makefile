LIBNAME = libcaffparser
LIBEXT =$(shell python3-config --extension-suffix)
FLAGS = -Wall -std=c++17 -I header/ -I ../import/pybind11/include/ $(shell python3-config --includes)
CLIBFLAG = -fPIC -shared
#ILIBF = -L../lib/ -Wl,-rpath=../lib/ -lcaffparser$(LIBEXT)
CC = g++


all: caffparser test

caffparser: caff.o parser.o
	mkdir -p ../lib ;\
	$(CC) $(FLAGS) $(CLIBFLAG) parser.o caff.o -o ../lib/$(LIBNAME)$(LIBEXT)

parser.o: src/parser.cpp
	$(CC) $(FLAGS) $(CLIBFLAG) -c src/parser.cpp -o parser.o

caff.o: src/caff.cpp
	$(CC) $(FLAGS) $(CLIBFLAG) -c src/caff.cpp -o caff.o


clean:
	rm -f -v *.o *.so *.out ../lib/*.so test/*.out
