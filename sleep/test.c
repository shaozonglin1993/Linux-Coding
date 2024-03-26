
#include <stdio.h>
#include "my_sleep.h"

int main()
{
	while(1){
		my_sleep(1);
		printf("1 sec passed!\n");
	}
	return 0;
}
