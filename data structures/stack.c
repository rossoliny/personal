#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct item
{
	struct item* next;
	int data;
} item;

typedef struct stack
{
	struct item* top;
	int8_t empty;
} stack;

stack* stack_init()
{
	stack* new_stack 	= malloc(sizeof(stack));

	new_stack->top 		= NULL;
	new_stack->empty 	= 1;

	return new_stack;
}

void stack_push(stack* stack, int data)
{
	item* new_item 	= malloc(sizeof(item));

	new_item->data 	= data;
	new_item->next 	= stack->top;
	stack->top 	= new_item;
	stack->empty 	= 0;
}

int stack_pop(stack* stack)
{
	item* top 	= stack->top;
	stack->top 	= top->next;
	int res 	= top->data;

	if(stack->top == NULL)
	{
		stack->empty = 1;
	}

	free(top);

	return res;
}

int stack_peek(stack* stack)
{
	return stack->top->data;
}

void stack_destroy(stack* stack)
{
	item* next = NULL;

	while(stack->top != NULL)
	{
		next = stack->top->next;
		free(stack->top);
		stack->top = next;
	}
	free(stack);
}

void stack_clear(stack* stack)
{
	item* next = NULL;

	while(stack->top != NULL)
	{
		next = stack->top->next;
		free(stack->top);
		stack->top = next;
	}
	stack->empty = 1;
}

void print_stack(stack* stack)
{
	while(!stack->empty)
	{
		printf("%d ", stack_pop(stack));
	}
	puts("");
	fflush(stdout);
}


int rearrange(stack* line_a, int N)
{
	stack* station = stack_init();

	int vagon;
	while(!line_a->empty)
	{
		vagon = stack_pop(line_a);

		if(vagon == N)
		{
			N--;
			while(!station->empty && station->top->data == N)
			{
				stack_pop(station);
				N--;
			}
		}
		else 
		{
			stack_push(station, vagon);
		}
	}

	while(!station->empty)
	{
		vagon = stack_pop(station);

		if(vagon == N)
		{
			N--;
		}
		else
		{
			return 0;
		}
	}
	
	stack_destroy(station);
	return 1;
}


int main()
{
	int N;

	stack* line_a = stack_init();
	while(1)
	{
		scanf("%d", &N);
		if(!N)
		{
			break;
		}
		
		while(1)
		{
			stack_clear(line_a);

			int n;
			scanf("%d", &n);
			if(!n)
			{
				puts("");
				break;
			}
			
			stack_push(line_a, n)
				;
			int i = 1;
			while(i < N)
			{
				scanf("%d", &n);
				stack_push(line_a, n);
				i++;
			}
			
			if(rearrange(line_a, N))
			{
				puts("Yes");
			}
			else 
			{
				puts("No");
			}
		}
	}
	stack_destroy(line_a);
}

