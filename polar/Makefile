polar: polarfn.o polarmain.o
	gcc polarfn.o polarmain.o -lm -o polar
polarfn.o: polarfn.c
	gcc -c polarfn.c 
polarmain.o: polarmain.c polarfn.h
	gcc -c polarmain.c
clean:
	rm *.o polar
