#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int strlen_(const char* s) {
	int res = 0;
	while(*s++ != '\0') {
		res++;
	}
	return res;
}

// only use with (char* left) allocated on dynamic memory
char* cat_d(char** left, const char* right, char sep) {
	int leftL = strlen_(*left);
	int newLen = leftL + strlen_(right) + 1;
	*left = realloc(*left, newLen * sizeof(char));
	char* i = *left + leftL;
	*i++ = sep;
	while(*i++ = *right++);
	return *left;
}

char* cat_(const char* left, const char* right, char sep) {
	int newLen = strlen_(left) + strlen_(right) + 1;
	char* res = malloc(newLen * sizeof(char));
	char* i = res;
	while(*i++ = *left++);
	*(i-1) = sep;
	while(*i++ = *right++);
	return res;
}

void swap(char* a, char* b) {
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

char* rev_(char* s) {
	char* last = s + strlen_(s) - 1;
	char* begin = s;
	printf("%c\n", *last);
	while(s < last) {
		swap(s, last);
		s++;
		last--;
	}
	return begin;
}

char* rev_d(const char* s) {
	int len = strlen_(s);
	char* new = malloc(len + 1);
	char* i = new;
	s = s + len - 1;
	while(len--) {
		*i++ = *s--;
	}
	*i = '\0';
	return new;
}



void mycopy(int* to, int* from, int count) {
	while(count--) {
		*to++ = *from++;
	}
}

int main(int argc, char** argv) {
	int n = 20000000;
    int* a = malloc(n * sizeof(int));//= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    int* b = malloc(n * sizeof(int));

    for(int i = 0; i < n; i++) {
    	a[i] = 'a';
    	b[i] = 'b';
    }
    a[n-1] = '\0';
    b[n-1] = '\0';

    clock_t s = clock();
    mycopy(a, b, n);
    clock_t e = clock(); 
    double elapsed = ((double)(e - s)) / (double)(CLOCKS_PER_SEC);
    printf("mycopy time    = %f\n", elapsed);
    fflush(stdout);

    s = clock();
    copy_duff(a, b, n);
    e = clock(); 
    elapsed = ((double)(e - s)) / (double)(CLOCKS_PER_SEC);
    printf("copy_duff time = %f\n", elapsed);
    fflush(stdout);
}
