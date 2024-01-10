build:
	gcc -c main.c baredb.c
	gcc main.o baredb.o -o main

clean:
	rm -r main main.o baredb.o database.db
