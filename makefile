FLAGS = -Wall -Wextra -std=c99

dijkstra: dijkstra.o binomial.o darray.o vertex.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o
	gcc $(FLAGS) dijkstra.o binomial.o darray.o vertex.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o -o dijkstra
dijkstra.o: dijkstra.c binomial.c darray.c vertex.c scanner.c comparator.c integer.c real.c string.c queue.c sll.c
	gcc $(FLAGS) -c dijkstra.c
binomial.o: binomial.c binomial.h
	gcc $(FLAGS) -c binomial.c
darray.o: darray.c darray.h
	gcc $(FLAGS) -c darray.c
vertex.o: vertex.c vertex.h
	gcc $(FLAGS) -c vertex.c
scanner.o: scanner.c scanner.h
	gcc $(FLAGS) -c scanner.c
comparator.o: comparator.c comparator.h
	gcc $(FLAGS) -c comparator.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
real.o: real.c real.h
	gcc $(FLAGS) -c real.c
string.o: string.c string.h
	gcc $(FLAGS) -c string.c
sll.o: sll.c sll.h
	gcc $(FLAGS) -c sll.c
queue.o: queue.c queue.h sll.h
	gcc $(FLAGS) -c queue.c
cleanbuild:
	clear
	make clean
	make
clean:
	rm -f dijkstra.o binomial.o darray.o vertex.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o dijkstra

test: ./dijkstra

	./dijkstra test.txt