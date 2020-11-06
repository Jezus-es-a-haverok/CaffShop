LIBNAME = libcaffparser
LIBEXT =$(shell python3-config --extension-suffix)
FLAGS = -O -z noexecstack -pie -D_FORTIFY_SOURCE=2 -D_FORTIFY_SOURCE=2 -Wl,-z,relro,-z,now -fstack-protector-all -Wall -std=c++17 -I header/ -I ../import/pybind11/include/ $(shell python3-config --includes)
CLIBFLAG = -fPIC -shared
#ILIBF = -L../lib/ -Wl,-rpath=../lib/ -lcaffparser$(LIBEXT)
CC = g++


all: caffparser test

caffparser: caff.o parser.o caffbinding.o
	mkdir -p ../lib ;\
	$(CC) $(FLAGS) $(CLIBFLAG) parser.o caff.o caffbinding.o -o ../lib/$(LIBNAME)$(LIBEXT)

parser.o: src/parser.cpp
	$(CC) $(FLAGS) $(CLIBFLAG) -c src/parser.cpp -o parser.o

caff.o: src/caff.cpp
	$(CC) $(FLAGS) $(CLIBFLAG) -c src/caff.cpp -o caff.o

caffbinding.o: src/caffbinding.cpp
	$(CC) $(FLAGS) $(CLIBFLAG) -c src/caffbinding.cpp -o caffbinding.o

clean:
	rm -f -v *.o *.so *.out ../lib/*.so test/*.out
