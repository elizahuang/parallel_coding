.PHONY: clean
pi.out : pi.o
	gcc -o pi.out pi.o -lpthread
pi.o : pi.c
	gcc -c pi.c -o pi.o -lpthread

clean:
	rm *.o
	rm *.out
