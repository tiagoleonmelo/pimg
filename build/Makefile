all: test

test: rgb.o grey.o bit.o test.o

	gcc -o test test.o rgb.o grey.o bit.o


test.o: ../src/test.c
	gcc -o test.o -c ../src/test.c -W -Wall


rgb.o: ../src/rgb.c
	gcc -o rgb.o -c ../src/rgb.c -W -Wall

grey.o: ../src/grey.c
	gcc -o grey.o -c ../src/grey.c -W -Wall

bit.o: ../src/bit.c
	gcc -o bit.o -c ../src/bit.c -W -Wall

clean:
	rm -rf *.o