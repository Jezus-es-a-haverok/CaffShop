LIBNAME = libcaffparser
LIBEXT =$(shell python3-config --extension-suffix)
PYFLAGS = -I ../import/pybind11/include/ $(shell python3-config --includes)
FLAGS =  -I header/ -O  -Wall -std=c++17
SECFLAGS = -z noexecstack -pie -D_FORTIFY_SOURCE=2 -D_FORTIFY_SOURCE=2 -Wl,-z,relro,-z,now -fstack-protector-all
CLIBFLAG = -fPIC -shared
WINEND = dll
LINEND = so
ILIBF = -L./test/bin/ -Wl,-rpath=./ -lcaffparser
WCC = x86_64-w64-mingw32-g++
CC = g++

default: libcaffparser cppcaffparser aflbin runtest

all: libcaffparser cppcaffparser win aflbin winbin runtest

win: wcppcaffparser winbin

# Python module
libcaffparser: caff.o parser.o caffbinding.o
	mkdir -p ../lib ;\
	$(CC) $(FLAGS) $(PYFLAGS) $(SECFLAGS) $(CLIBFLAG) parser.o caff.o caffbinding.o -o ../lib/$(LIBNAME)$(LIBEXT)

parser.o: src/parser.cpp
	$(CC) $(FLAGS) $(PYFLAGS) $(SECFLAGS) $(CLIBFLAG) -c src/parser.cpp -o parser.o

caff.o: src/caff.cpp
	$(CC) $(FLAGS) $(PYFLAGS) $(SECFLAGS) $(CLIBFLAG) -c src/caff.cpp -o caff.o

caffbinding.o: src/caffbinding.cpp
	$(CC) $(FLAGS) $(PYFLAGS) $(SECFLAGS) $(CLIBFLAG) -c src/caffbinding.cpp -o caffbinding.o

# Linux shared library
cppcaffparser: ccaff.o cparser.o
	mkdir -p ../lib ;\
	$(CC) $(FLAGS) $(SECFLAGS) $(CLIBFLAG) cparser.o ccaff.o -o ../lib/$(LIBNAME).$(LINEND)

cparser.o: src/parser.cpp
	$(CC) $(FLAGS) $(SECFLAGS) $(CLIBFLAG) -c src/parser.cpp -o cparser.o

ccaff.o: src/caff.cpp
	$(CC) $(FLAGS) $(SECFLAGS) $(CLIBFLAG) -c src/caff.cpp -o ccaff.o

# Windows shared librry
wcppcaffparser: wccaff.o wcparser.o
	mkdir -p ../lib ;\
	$(WCC) $(FLAGS) $(CLIBFLAG) wcparser.o wccaff.o -o ../lib/$(LIBNAME).$(WINEND)

wcparser.o: src/parser.cpp
	$(WCC) $(FLAGS) $(CLIBFLAG) -c src/parser.cpp -o wcparser.o

wccaff.o: src/caff.cpp
	$(WCC) $(FLAGS) $(CLIBFLAG) -c src/caff.cpp -o wccaff.o

# Linux executable
aflbin: test.o cppcaffparser
	cp -f -v ../lib/libcaffparser.so test/bin/ ; \
	$(CC) $(FLAGS) $(ILIBF) $(SECFLAGS) test/test.o -o test/bin/test.out

test.o: test/main.cpp
	$(CC) $(FLAGS) $(ILIBF) $(SECFLAGS) -c test/main.cpp -o test/test.o

# Windows executable
winbin: wtest.o wcppcaffparser
	cp -v ../lib/libcaffparser.dll test/bin/ ; \
	cp -v /usr/x86_64-w64-mingw32/bin/libstdc++-6.dll test/bin/ ; \
	cp -v /usr/x86_64-w64-mingw32/bin/libgcc_s_seh-1.dll test/bin/ ; \
	cp -v /usr/x86_64-w64-mingw32/bin/libwinpthread-1.dll test/bin/ ; \
	$(WCC) $(FLAGS) $(ILIBF) test/wtest.o -o test/bin/test.exe

wtest.o: test/main.cpp
	$(WCC) $(FLAGS) $(ILIBF) -c test/main.cpp -o test/wtest.o

runtest: libcaffparser
	mkdir test/python/output ; \
	cd test/python ; \
	python3 test.py ; \
	cd ../..

clean:
	rm -f -v *.o *.so *.out ../lib/*.so test/*.out ../lib/*.dll test/*.o test/*.so test/bin/*.out test/bin/*.so; \
	rm -f -v -r ./test/python/output
