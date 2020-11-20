#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SL_MAX_HEIGHT 12

typedef struct slist_node
{
	struct slist_node*	next[SL_MAX_HEIGHT];
	char* 			key;
	float 			value;
	int 			height;
} slist_node_t;

int slist_rand(int max)
{
	int res = 1;
	while(res < max && (rand() > RAND_MAX / 2))
	{
		res++;
	}

	return res;
}

slist_node_t* slist_node_init(char* key, float value, int height)
{
	slist_node_t* new_node = malloc(sizeof(slist_node_t));
	new_node->key = strdup(key);
	new_node->height = height;
	new_node->value = value;

	return new_node;
}

void slist_node_destroy(slist_node_t* node)
{
	free(node->key);
	node->key = NULL;

	free(node);
	node = NULL;
}

slist_node_t* slist_init()
{
	srand((unsigned int) time(NULL));

	slist_node_t* first = calloc(1, sizeof(slist_node_t));
	if(!first)
	{
		fputs("SKIPLIST INIT ERROR: Out of memory", stderr);
		fflush(stderr);
	}
	first->height = SL_MAX_HEIGHT;

	return first;
}

void slist_destroy(slist_node_t* first)
{
	while(first)
	{
		slist_node_t* temp = first->next[0];
		slist_node_destroy(first);
		first = temp;
	}
	first = NULL;
}

slist_node_t* slist_search(slist_node_t* first, char* key)
{
	int curr_level = first->height - 1;
	slist_node_t* curr_node = first;

	if(!strcmp(curr_node->key, key))
	{
		return curr_node;
	}

	while(curr_node && curr_level >= 0) {
		if(curr_node->next[curr_level] == NULL)
		{
			--curr_level;
			continue;
		}

		slist_node_t* next_node = curr_node->next[curr_level];

		int c = strcmp(next_node->key, key);
		if(!c)
		{
			return next_node;
		}
		else if(c < 0)
		{
			curr_node = next_node;
		}
		else 
		{
			--curr_level;
		}
	}

	return NULL;
}


slist_node_t* slist_insert(slist_node_t* first, char* key, float value)
{
	int curr_level = first->height - 1;
	slist_node_t* curr_node = first;
	slist_node_t* curr_nodes[SL_MAX_HEIGHT];

	if(curr_node->key == NULL)
	{
		curr_node->key = strdup(key);
		curr_node->value = value;
		return curr_node;
	}

	while(curr_level >= 0 && curr_node)
	{
		if(curr_node->next[curr_level] == NULL)
		{
			curr_nodes[curr_level] = curr_node;
			--curr_level;
			continue;
		}
		slist_node_t* next_node = curr_node->next[curr_level];

		int c = strcmp(next_node->key, key);
		if(!c)
		{
			next_node->value = value;
			return next_node;
		}
		else if(c < 0)
		{
			curr_node = next_node;
		}
		else 
		{
			curr_nodes[curr_level] = curr_node;
			--curr_level;
		}
	}
	slist_node_t* new_node = slist_node_init(key, value, slist_rand(first->height));

	int level = SL_MAX_HEIGHT - 1;
	while(level > new_node->height)
	{
		new_node->next[level] = NULL;
		--level;
	}
	
	while(level >= 0)
	{
		new_node->next[level] = curr_nodes[level]->next[level];
		curr_nodes[level]->next[level] = new_node;
		--level;
	}

	return curr_node;
}

void slist_print(slist_node_t* list)
{
	while(list)
	{
		printf("(%s, %.2f)\n", list->key, list->value);
		fflush(stdout);
		list = list->next[0];
	}
}

int main()
{
	int n;
	scanf("%d", &n);

	while(n--)
	{
		int p;
		scanf("%d", &p);

		slist_node_t* skiplist = slist_init();
		static char buff[256];
		float price;
		while(p--)
		{
			scanf("%s %f", buff, &price);
			slist_insert(skiplist, buff, price);
		}
		
		scanf("%d", &p);
		float res = 0;
		int amnt;
		while(p--)
		{
			scanf("%s %d", buff, &amnt);
			slist_node_t* item = slist_search(skiplist, buff);

			res += item->value * amnt;
		}
		printf("R$ %.2f\n", res);

		slist_destroy(skiplist);
	}

	return 0;
}
