CC = gcc
CFLAGS = -Wall -Wextra

steganography: main.o steganography.o
	$(CC) $(CFLAGS) -o steganography main.o steganography.o

main.o: main.c steganography.h
	$(CC) $(CFLAGS) -c main.c

steganography.o: steganography.c steganography.h
	$(CC) $(CFLAGS) -c steganography.c

clean:
	rm -f *.o steganography

