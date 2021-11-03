.PHONY: clean
pi.out : hw0_monteCarlo_c.o
	gcc -o pi.out hw0_monteCarlo_c.o
hw0_monteCarlo_c.o : hw0_monteCarlo.c
	gcc -c hw0_monteCarlo.c -o hw0_monteCarlo_c.o

clean:
	rm *.o
	rm *.out
