OBJS = dll.o vertex.o scanner.o array.o binheap.o helper.o prim.o
OPTS = -Wall -g -std=c99

prim : $(OBJS)
	gcc $(OPTS) $(OBJS) -o prim -lm

prim.o : prim.c helper.h scanner.h array.h vertex.h binheap.h dll.h
	gcc $(OPTS) -c prim.c

helper.o: helper.c helper.h scanner.h array.h vertex.h dll.h binheap.h
	gcc $(OPTS) -c helper.c

binheap.o: binheap.c binheap.h dll.h vertex.h
	gcc $(OPTS) -c binheap.c

scanner.o: scanner.c scanner.h
	gcc $(OPTS) -c scanner.c

vertex.o: vertex.c vertex.h array.h dll.h
	gcc $(OPTS) -c vertex.c

array.o: array.c array.h
	gcc $(OPTS) -c array.c

dll.o: dll.c dll.h
	gcc $(OPTS) -c dll.c

clean:
	rm -f $(OBJS) prim

test:
	prim s.txt
