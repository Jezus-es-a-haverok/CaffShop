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

clean:
	make -C caffparser/ clean ; \
	rm -f -v -r codedoc

doxygen:
	doxygen Doxyfile ; \
	echo "Open codedoc\html\index.html in browser"
