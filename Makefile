default:
	make -C caffparser/

all:
	make -C caffparser/ all

libcaffparser:
	make -C caffparser/ libcaffparser

aflbin:
	make -C caffparser/ aflbin

runtest:
	make -C caffparser/ runtest

win:
	make -C caffparser/ win
	
mac:
	make -C caffparser/ mac

clean:
	make -C caffparser/ clean ; \
	rm -f -v -r codedoc

initrelease:
	mkdir -p Release ; \
	mkdir -p Release/Linux ; \
	mkdir -p Release/Windows ; \
	cp -v /usr/x86_64-w64-mingw32/bin/libstdc++-6.dll Release/Windows/ ; \
	cp -v /usr/x86_64-w64-mingw32/bin/libgcc_s_seh-1.dll Release/Windows/ ; \
	cp -v /usr/x86_64-w64-mingw32/bin/libwinpthread-1.dll Release/Windows/ ; \
	cp -vr /usr/x86_64-w64-mingw32/lib/python3.8 Release/Windows/ ; \
	cp -v /usr/x86_64-w64-mingw32/bin/libssp-0.dll Release/Windows/ ; \
	cp -v /usr/x86_64-w64-mingw32/bin/libpython3.8.dll Release/Windows/ ; \
	cp -v /usr/x86_64-w64-mingw32/bin/python3.8.exe Release/Windows/python3.exe

release: all
	cp -fv lib/*.dll Release/Windows/ ; \
	cp -fv lib/*.pyd Release/Windows/ ; \
	cp -fv lib/*so Release/Linux/ ; \
	cp -fv caffparser/test/bin/test.out Release/Linux/ ; \
	cp -fv caffparser/test/bin/test.exe Release/Windows/ ; \
	cp -fv caffparser/test/python/test.py Release/Linux/ ; \
	cp -fv caffparser/test/python/test.py Release/Windows/ ; \
	cp -fv caffparser/test/bin/runpython.bat Release/Windows/ ; \
	zip -v -r Release/Release.zip Release/

doxygen:
	doxygen Doxyfile ; \
	echo "Open codedoc\html\index.html in browser"
