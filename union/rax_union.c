#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

typedef union
{
	int64_t r;
	int32_t e;
	int16_t w; // word
	int8_t h;
	int8_t l;
} register64;

void print_register64_state(const register64* reg, const char* reg_name)
{
	printf("\tstate of %s:\n", reg_name);

	printf("\t\tr part: 0x%016" PRIx64 "\t\n",	reg->r );
	printf("\t\te part: 0x%08" PRIx32 "\t\n", 	reg->e );
	printf("\t\tw part: 0x%04" PRIx16 "\t\n", 	reg->w );
	printf("\t\th part: 0x%02" PRIx8 "\t\n", 	reg->h );
	printf("\t\tl part: 0x%02" PRIx8 "\t\n", 	reg->l );
}

int main(int argc, char** argv)
{

	puts("SIMULATE REGISTERS:");
	{
		register64 register64;
		puts("union register64 {");
		printf("\tint64_t r;\t\t\\\\size = %zu\n", sizeof(register64.r));
		printf("\tint32_t e;\t\t\\\\size = %zu\n", sizeof(register64.e));
		printf("\tint16_t w;\t\t\\\\size = %zu\n", sizeof(register64.w));
		printf("\tint8_t h;\t\t\\\\size = %zu\n", sizeof(register64.h));
		printf("\tint8_t l;\t\t\\\\size = %zu\n", sizeof(register64.l));
		puts("};");
	}
	printf("sizeof(register64) = %zu bits\n", sizeof(register64) * 8);

	puts("\ncreateing rax register");
	register64 rax;
	print_register64_state(&rax, "rax");

	puts("\nsetting value of rax to 0x1111111100000000");
	rax.r = 0x1111111100000000;
	print_register64_state(&rax, "rax");

	puts("\nsetting value of eax to 0x11110000");
	rax.e = 0x11110000;
	print_register64_state(&rax, "rax"); 

	puts("\nsetting value of ax to 0x1100");
	rax.w = 0x1100;
	print_register64_state(&rax, "rax");

	puts("\nsetting value of ah to 0x11");
	rax.h = 0x11;
	print_register64_state(&rax, "rax");

	puts("\nsetting value of al to 0x00");
	rax.l = 0x00;
	print_register64_state(&rax, "rax");

	return  0;
}
