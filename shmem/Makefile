.PHONY:all
all:server client
server:server.c shmem.c
	gcc -o server server.c shmem.c -g
client:client.c shmem.c
	gcc -o client client.c shmem.c
.PHONY:clean
clean:
	rm -f server client
