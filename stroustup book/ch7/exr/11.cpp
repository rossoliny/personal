#include <cstdarg>
#include <cstdio>
#include <cstring>

void error(const char* format ...) {
	va_list list;
	va_start(list, format);

	int len = strlen(format);

	for(int i = 0; i < len; i++) {
		switch(format[i]) {
			case '%':
			{
				switch(format[++i]) {
					case 's':
					{
						char* str = va_arg(list, char*);
						while(*str) {
							putc(*str++, stderr);
						}
						break;
					}
					case 'c':
					{
						const char ch = (char) va_arg(list, int);
						putc(ch, stderr);
						break;
					}
					case 'd':
					{
						int num = va_arg(list, int);
						if(num < 0) {
							putc('-', stderr);
							num = -num;
						}
						char buffer[20];
						buffer[0] = '\0';
						char* buff = buffer + 1;

						while(num != 0) {
							*buff++ = (char) ((num % 10) + '0');
							num /= 10;
						}

						while(*--buff) {
							putc(*buff, stderr);
						}
						break;
					}
					case '%':
						putc('%', stderr);
						putc('%', stderr);
						break;
					default: 
						putc('%', stderr);
						putc(format[i], stderr);
						break;
				}
				break;
			}
			default:
			{
				putc(format[i], stderr);
			}
		}
	}
	va_end(list);
}

int main(int argc, char** argv) {
	

	error("hello %s %% % % % you are %d years old, right?\n", "isa", 23);
	error("this must perint letters a, b and c: %c, %c, %c\n", 'a', 'b', 'c');


	return 0;

}
