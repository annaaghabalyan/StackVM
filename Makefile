CC=gcc
all: add_example.c interpretator.c stackVM.c 
	$(CC) add_example.c interpretator.c stackVM.c -o add_example
	$(CC) call_example.c interpretator.c stackVM.c -o call_example
