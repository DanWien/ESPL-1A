all: encoder

encoder: encoder.o
	gcc -m32 -g -Wall -o encoder encoder.o

# Depends on the source and header files
encoder.o: encoder.c 
	gcc -g -Wall -m32 -c -o encoder.o encoder.c

.PHONY: clean

#Clean the build directory
clean:
	rm -f encoder encoder.o