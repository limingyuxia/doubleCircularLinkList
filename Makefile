
all: list

list: list.o demo.o
	$(CC) $^ -o $@

clean:
	rm -rf list *.o