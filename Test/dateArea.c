#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<float.h>

void main()
{
	printf("char date is from %d to %d.\n",CHAR_MIN,CHAR_MAX);
	printf("unsigned char date is from 0 to %u.\n",UCHAR_MAX);
	printf("\n");
	printf("short date is from %d to %d.\n",SHRT_MIN,SHRT_MAX);
	printf("unsigned short date is from 0 to %u.\n",USHRT_MAX);

	printf("\n");
	printf("int date is from %d to %d.\n",INT_MIN,INT_MAX);
	printf("unsigned int date is from 0 to %u.\n",UINT_MAX);
	printf("\n");

	printf("long date is from %d to %d.\n",LONG_MIN,LONG_MAX);
	printf("unsigned long date is from 0 to %lu.\n",ULONG_MAX);
	printf("\n");

	printf("long long date is from %lld to %lld.\n",LLONG_MIN,LLONG_MAX);
	printf("unsigned long long date is from 0 to %llu.\n",ULLONG_MAX);
	printf("\n");

	printf("float date is from %.3e to %.3e.\n",FLT_MIN,FLT_MAX);
	printf("\n");

	printf("double date is from %.3e to %.3e.\n",DBL_MIN,DBL_MAX);
	printf("\n");

	printf("long double date is from %.3Le to %.3Le\n",LDBL_MIN,LDBL_MAX);
	printf("\n");

	printf("the accuracy of float date is %u\n",FLT_DIG);
	printf("the accuracy of double date is %u\n",DBL_DIG);
	printf("the accuracy of long double date is %u\n",LDBL_DIG);
}
