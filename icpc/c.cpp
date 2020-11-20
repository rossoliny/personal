#include <iostream>
#include <queue>
#include <stack>
#include <string>

using namespace std;
#define stack deque
#define push push_back
#define pop pop_back
#define top back

struct card
{
	char mast;
	char rang;
};

void print_card(card c)
{	
	cout << "Card { " << c.mast << ", " << c.rang << " }" << endl;
}

void print_stack(stack<card>& s) 
{
	while(!s.empty())
	{
		print_card(s.top());
		s.pop();
	}
}

int special(card c)
{
	switch(c.rang) {
		case 'J':
			return 1;
		case 'Q':
			return 2;
		case 'K':
			return 3;
		case 'A':
			return 4;
	}
	return 0;
}

void merge(stack<card>& cards, stack<card>& kucha)
{
	while(!kucha.empty()) 
	{
		card ca = kucha.top();
		cards.push_front(ca);
		kucha.pop();
	}
}

int rcount = 0;

int round(stack<card>& p1, stack<card>& p2, stack<card>& kucha, int count, bool player1)
{
	while(!p1.empty() && !p2.empty() && count--) 
	{
		card c = p1.top();
		kucha.push(c);
		p1.pop();
		
		int count = special(c);
		if(count != 0) 
		{
			int p = round(p2, p1, kucha, count, !player1);

			if(p) 
			{
				merge(p1, kucha);
			}
			else
			{
				merge(p2, kucha);
			}
		}

	}

	rcount++;
	printf("\nRound #%d: \np1 = %d\np2 = %d\nkucha = %d\n", rcount, p1.size(), p2.size(), kucha.size());

	if(player1) 
	{
		return 0;
	}
	else 
	{
		return 1;
	}
	//end
}

int main() 
{
	stack<card> p1;
	stack<card> p2;

	char c;
	int i = 0;
	while(1) 
	{
		cin >> c;
		if(c == '#')
		{
			break;
		}
		
		cin.putback(c);

		i = 0;
		card card;
		while(i < 26) {
			cin >> card.mast;
			cin >> card.rang;
			
			p1.push(card);
			
			cin >> card.mast;
			cin >> card.rang;

			p2.push(card);

			i++;
		}
	}
	/*	
	puts("STACK 1");
	print_stack(p1);
	puts("\nSTACK 2");
	print_stack(p2);
	*/

	stack<card> kucha;

	int k = 0;
	bool player1 = true;
	while(!p1.empty() && !p2.empty())
	{
		if(player1) {
			k = kucha.size();
			player1 = round(p1, p2, kucha, 1, true);
		}
		else {
			k = kucha.size();
			player1 = round(p2, p1, kucha, 1, false);
		}
	}
	if(p1.empty()) 
	{
		printf("2 %d\n", p2.size() - k);
	}
	else if (p2.empty())
	{
		printf("1 %d\n", p1.size() - k);
	}
	else 
	{
		puts("ERROR");
	}

}
