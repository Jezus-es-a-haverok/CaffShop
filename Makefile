all:
	make -C caffparser/

test:
	make -C caffparser/ test

clean:
	make -C caffparser/ clean
