.PHONY:all
all:server client
server:server.c
	gcc -o server server.c comm.c
client:client.c
	gcc -o client client.c comm.c
.PHONY:clean
clean:
	rm client server
