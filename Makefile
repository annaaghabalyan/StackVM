CC=gcc
all: main.c interpretator.c stackVM.c 
	$(CC) main.c interpretator.c stackVM.c -o main
