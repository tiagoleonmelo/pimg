all: pimg

read_img: formats.o read_img.o

	gcc -o read_img read_img.o formats.o


read_img.o: read_img.c
	gcc -o read_img.o -c read_img.c -W -Wall


formats.c: formats.c
	gcc -o formats.o -c formats.c -W -Wall

clean:
	rm -rf *.o


