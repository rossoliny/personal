#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv) 
{
	char c;
	int count = 0;

	while( (c = getchar()) != '\n') {
		switch(c) {
			case ' ':
				count++;
				break;
		}
	}
	printf("%d\n", count);	
}
