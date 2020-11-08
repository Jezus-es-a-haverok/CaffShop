LIBNAME = libcaffparser
LIBEXT =$(shell python3-config --extension-suffix)
PYFLAGS = -I ../import/pybind11/include/ $(shell python3-config --includes)
FLAGS =  -I header/ -O -z noexecstack -pie -D_FORTIFY_SOURCE=2 -D_FORTIFY_SOURCE=2 -Wl,-z,relro,-z,now -fstack-protector-all -Wall -std=c++17
CLIBFLAG = -fPIC -shared
WINEND = dll
LINEND = so
ILIBF = -L./test/bin/ -Wl,-rpath=./ -lcaffparser
WCC = x86_64-w64-mingw32-g++
CC = g++

default: libcaffparser cppcaffparser aflbin runtest

all: libcaffparser cppcaffparser win aflbin runtest

win: wcppcaffparser

libcaffparser: caff.o parser.o caffbinding.o
	mkdir -p ../lib ;\
	$(CC) $(FLAGS) $(PYFLAGS) $(CLIBFLAG) parser.o caff.o caffbinding.o -o ../lib/$(LIBNAME)$(LIBEXT)

parser.o: src/parser.cpp
	$(CC) $(FLAGS) $(PYFLAGS) $(CLIBFLAG) -c src/parser.cpp -o parser.o

caff.o: src/caff.cpp
	$(CC) $(FLAGS) $(PYFLAGS) $(CLIBFLAG) -c src/caff.cpp -o caff.o

caffbinding.o: src/caffbinding.cpp
	$(CC) $(FLAGS) $(PYFLAGS) $(CLIBFLAG) -c src/caffbinding.cpp -o caffbinding.o

cppcaffparser: ccaff.o cparser.o
	mkdir -p ../lib ;\
	$(CC) $(FLAGS) $(CLIBFLAG) cparser.o ccaff.o -o ../lib/$(LIBNAME).$(LINEND)

cparser.o: src/parser.cpp
	$(CC) $(FLAGS) $(CLIBFLAG) -c src/parser.cpp -o cparser.o

ccaff.o: src/caff.cpp
	$(CC) $(FLAGS) $(CLIBFLAG) -c src/caff.cpp -o ccaff.o

wcppcaffparser: wccaff.o wcparser.o
	mkdir -p ../lib ;\
	$(CC) $(FLAGS) $(CLIBFLAG) wcparser.o wccaff.o -o ../lib/$(LIBNAME).$(WINEND)

wcparser.o: src/parser.cpp
	$(CC) $(FLAGS) $(CLIBFLAG) -c src/parser.cpp -o wcparser.o

wccaff.o: src/caff.cpp
	$(CC) $(FLAGS) $(CLIBFLAG) -c src/caff.cpp -o wccaff.o

aflbin: test.o cppcaffparser
	cp -v ../lib/libcaffparser.so test/bin/ ; \
	$(CC) $(FLAGS) $(ILIBF) test/test.o -o test/bin/test.out

test.o: test/main.cpp
	$(CC) $(FLAGS) $(ILIBF) -c test/main.cpp -o test/test.o

runtest: libcaffparser
	mkdir test/python/output ; \
	cd test/python ; \
	python3 test.py ; \
	cd ../..

clean:
	rm -f -v *.o *.so *.out ../lib/*.so test/*.out ../lib/*.dll test/*.o test/*.so test/bin/*.out test/bin/*.so; \
	rm -f -v -r ./test/python/output
