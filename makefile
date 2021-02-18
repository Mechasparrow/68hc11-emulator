
program: main.o cpu.o
	gcc -o program main.o cpu.o

reader: reader.o
	gcc -o reader reader.o

reader.o: reader.c cpu.h
	gcc -c reader.c

main.o: main.c cpu.h
	gcc -c main.c

cpu.o: cpu.c cpu.h
	gcc -c cpu.c

clean:
	rm *.o program reader
