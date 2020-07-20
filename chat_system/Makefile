ROOT_PATH=$(shell pwd)
CLIENT=$(ROOT_PATH)/client
SERVER=$(ROOT_PATH)/server
ALL=$(CLIENT) $(SERVER)

.PHONY:output
output:
	@for i in 'echo' $(ALL)';\
	do\
		cd $$i;
		make;
		cd -;\
	done


