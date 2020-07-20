ROOT_PATH=$(shell pwd)
BIN=httpd
cc=gcc
SRC=httpd.c
OBJ=$(SRC:.c=.o)
LIB=-lpthread
FLAGS=#-D_DEBUG_
CGI=$(ROOT_PATH)/htdoc/cgi $(ROOT_PATH)/mysql_connect

.PHONY:all
all: $(BIN) cgi

$(SIN):$(OBJ)
	$(CC) -o $@ $^ $(LIB)
%.o:%.c
	$(CC) -c $< $(FLAGS)

.PHONY:cgi
cgi:
	for name in 'echo $(CGI)':\
	do\
		cd $$name;\
		make;\
		cd -;\
	done

.PHONY:clean
clean:
	rm -rf *.o $(BIN) output
	for name in 'echo $(CGI)';\
	do\
		cd $$name;\
		make clean;\
		cd -;
	done

.PHONY:output
output:
	mkdir -p output/lib
	mkdir -p output/htdoc/cgi
	mkdir -p output/htdoc/imag
	cp -f httpd output
	cd htdoc/cgi/cgi_math output/htdoc/cgi
	cp htdoc/imag/* output/hhtdoc/imag
	cd htdoc/index.html output/htdoc
	cp htdoc/select.html output /htdoc
	cp mysql connect/cgi_insert output/htdoc/cgi
	cp mysql_connect/cgi_select output/htdoc/cgi
	cp mysql_connect/cgi_select output/htdoc/cgi
	cp start.sh output
	cp lib/lib/* output/lib

.PHONY:debug
debug:
	@echo $(RPPT_PSTH)
	@echo $(BIN)
	@echo $(CC)
	@echo $(SRC)
	@echo $(OBJ)

