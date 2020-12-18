#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct pair
{
	char* key;
	float data;
} pair_t;


#define SIZE 100

pair_t* contents[SIZE];

unsigned int hash(char* key)
{
	unsigned int res = 5381;
	unsigned char c;

	while(c = *key++)
	{
		res = res * 33 + (unsigned int)c;
	}

	return res % SIZE;
}

pair_t* search(char* key)
{
	unsigned int index = hash(key);

	while(contents[index] != NULL)
	{
		if(!strcmp(contents[index]->key, key))
		{
			return contents[index];
		}
		index++;
		index %= SIZE;
	}
	return NULL;
}

void insert(char* key, float data)
{
	pair_t* item = malloc(sizeof(pair_t));
	item->data = data;

	int key_len = strlen(key) + 1;
	item->key = malloc(key_len);
	strncpy(item->key, key, key_len);

	unsigned int index = hash(key);
	
	while(contents[index] != NULL)
	{
		index++;
		index %= SIZE;
	}

	contents[index] = item;
}

void print_map()
{
	unsigned int i = 0;
	printf("\nMAP\n\n");
	while(i < SIZE)
	{
		if(contents[i])
		{
			printf("(%s: %.2f)\n", contents[i]->key, contents[i]->data);
		}
		i++;
	}
	printf("\nMAP END\n\n");
	fflush(stdout);
}

void clear_map()
{
	memset(contents, 0, sizeof(contents));
}

int main(int argc, char** argv)
{
	int n;	
	scanf("%d", &n);

	while(n--)
	{
		clear_map();
		float res = 0;
		char name[256];

		int p;
		scanf("%d", &p);
		while(p--)
		{
			float price;

			scanf("%s %f", name, &price);

			insert(name, price);
		}
		scanf("%d", &p);
		while(p--)
		{
			int amnt = 0;

			scanf("%s %d", name, &amnt);

			pair_t* item = search(name);
			res += item->data * amnt;
		}
		printf("R$ %.2f\n", res);
	}
	return 0;
}
