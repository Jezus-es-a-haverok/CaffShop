all:
	make -C caffparser/

test:
	make -C caffparser/ test

clean:
	make -C caffparser/ clean ; \
	rm -f -v -r codedoc

doxygen:
	doxygen Doxyfile ; \
	echo "Open codedoc\html\index.html in browser"
