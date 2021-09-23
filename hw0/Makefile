.PHONY: clean
hw0_monteCarlo_c.out : hw0_monteCarlo_c.o
        gcc -o hw0_monteCarlo_c.out hw0_monteCarlo_c.o
hw0_monteCarlo_c.o : hw0_monteCarlo.c
        gcc -c hw0_monteCarlo.c -o hw0_monteCarlo_c.o
hw0_monteCarlo_cc.out : hw0_monteCarlo_cc.o
        g++ -o hw0_monteCarlo_cc.out hw0_monteCarlo_cc.o
hw0_monteCarlo_cc.o : hw0_monteCarlo.cc
        g++ -c hw0_monteCarlo.cc -o hw0_monteCarlo_cc.o 
clean:
        rm *.o
        rm *.out