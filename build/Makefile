all: read_img

read_img: formats.o read_img.o

	gcc -o read_img read_img.o formats.o


read_img.o: ../src/read_img.c
	gcc -o read_img.o -c ../src/read_img.c -W -Wall


formats.o: ../src/formats.c
	gcc -o formats.o -c ../src/formats.c -W -Wall

clean:
	rm -rf *.o


