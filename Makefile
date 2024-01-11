build:
	gcc -c baredb.c -o libbaredb.o
	gcc -c main.c -o main.o
	gcc main.o libbaredb.o -o main

clean: libbaredb.o main main.c database.db
	rm main main.o libbaredb.o database.db

install: libbaredb.o baredb.h
	ar rcs libbaredb.a libbaredb.o
	sudo cp libbaredb.a /usr/lib/
	sudo cp baredb.h /usr/include/
	sudo ldconfig
	rm libbaredb.a
