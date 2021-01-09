#include <stdio.h>
#include <stdint.h>


typedef union
{
	int first, second;
} fused_int;

union S
{
    int32_t n;     // occupies 4 bytes
    uint16_t s[2]; // occupies 4 bytes
   	uint8_t c;     // occupies 1 byte
}; 

// without pragma size will be 16 because of int padding
// int is aligned by 4, 14 is not multiple of 4 
// so it's size = nearest multiple of 4 that is > than 14.
#pragma pack(push, 1)
typedef union some_union
{
	int c;
	char data[14];
} some_union;
#pragma pack(pop)


int main(int argc, char** argv)
{
	fused_int fi;

	printf("first: %d\nsecond: %d\n", fi.first, fi.second);

	fi.first = 10;
	printf("first: %d\nsecond: %d\n", fi.first, fi.second);
	
	fi.second += 5;
	printf("first: %d\nsecond: %d\n", fi.first, fi.second);

	some_union su;
	int sizeof_some_union = sizeof su;
	printf("sizeof(some_union) = %d\n", sizeof_some_union);

	printf("sizeof(union S) = %zu\n", sizeof(union S));

	return  0;
}
