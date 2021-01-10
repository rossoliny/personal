#include <stdio.h>

int main()
{
	puts("at least 1 byte");
	printf("sizeof char: %zu\n", sizeof(char));
	printf("sizeof unsigned char: %zu\n", sizeof(unsigned char));
	printf("sizeof signed char: %zu\n", sizeof(signed char));

	puts("\nat least 2 btyes");
	printf("sizeof short int: %zu\n", sizeof(short int));
	printf("sizeof unsigned short int: %zu\n", sizeof(unsigned short int));
	printf("sizeof signed short int: %zu\n", sizeof(signed short int));

	puts("\nat least 2 bytes");
	printf("sizeof int: %zu\n", sizeof(int));
	printf("sizeof signed int: %zu\n", sizeof(signed int));
	printf("sizeof unsigned int: %zu\n", sizeof(unsigned int));

	puts("\nat least 4 bytes");
	printf("sizeof long int: %zu\n", sizeof(long int));
	printf("sizeof signed long int: %zu\n", sizeof(signed long int));
	printf("sizeof unsigned long int: %zu\n", sizeof(unsigned long int));

	puts("\nat least 8 bytes");
	printf("sizeof long long int: %zu\n", sizeof(long long int));
	printf("sizeof signed long long int: %zu\n", sizeof(signed long long int));
	printf("sizeof unsigned long long int: %zu\n", sizeof(unsigned long long int));
}
