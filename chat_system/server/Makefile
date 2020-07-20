ROOT_PATH=$(shell pwd)
CC=g++
SERVER=udp_server

SRC=$(shell ls $(ROOT_PATH)/*.cpp)
OBJ=$(SRC:.cpp=.o)

$(SERVER):$(OBJ)
	$(CC) -o $@ $^
%.o:%.cpp
	$(CC) -c $<

.PHONY:clean
clean:
	rm -f $(SERVER) 

.PHONY:debug
debug:
	@echo $(ROOT_PATH)
	@echo $()
	@echo $()

