.PHONY:all
all:test
test:test.c fork.c
	gcc -o test fork.c test.c -g
.PHONY:clean
clean:
	rm test
