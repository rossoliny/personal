#include <vector>
#include <sstream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <stack>

using namespace std;

unsigned char a = 0;
unsigned char b = 0;
unsigned char c = 0;
unsigned char d = 0;
unsigned char e = 0;
unsigned char f = 0;
unsigned char g = 0;

enum command
{
	ADD,
	REP,
	ASN,
	END,
	NOP
};

bool var(char ch)
{
	switch(ch)
	{
		case 'A':
			return true;

		case 'B':
			return true;

		case 'C':
			return true;

		case 'D':
			return true;

		case 'E':
			return true;

		case 'F':
			return true;

		case 'G':
			return true;

	}
	return false;
}

stack<char> vars;
stack<int> reps;

command read()
{
	string line;
	getline(cin, line);	

	//cout << "Line: " << line << endl;
	
	char ch = line[0];

	if(var(ch))
	{
		vars.push(ch);
		if(line.size() == 9) 
		{
			vars.push(line[4]);
			vars.push(line[8]);
			return ADD;
		}
		else 
		{
			char num;
			switch(line.size())
			{
				case 5:
					num = line[4] - '0';	
					break;
				case 6:
					num = line[4] - '0';	
					break;
				case 7:
					num = line[4] - '0';
					break;
			}
			vars.push(num);
			return ASN;	
		}
	}

	int n;
	switch(line[0])	
	{
		case 'r':
			n = line[7] - '0';
			reps.push(n);
			return REP;
		case 'e':
			return END;
	}
	return NOP;
}

unsigned char* addr(char arg)
{
	unsigned char* res = nullptr;
	switch(arg)
	{
		case 'A':
			res = &a;
			break;
		case 'B':
			res = &b;
			break;
		case 'C':
			res = &c;
			break;
		case 'D':
			res = &d;
			break;
		case 'E':
			res = &e;
			break;
		case 'F':
			res = &f;
			break;
		case 'G':
			res = &g;
			break;
	}
	return res;
}
int addc = 0;
void add()
{
	
	addc++;
	char dst;
	char a;
	char b;

	b = vars.top(); vars.pop();
	a = vars.top(); vars.pop();
	dst = vars.top(); vars.pop();

	unsigned char* dst_p;
	unsigned char* a_p;
	unsigned char* b_p;

	dst_p = addr(dst);
	a_p = addr(a);
	b_p = addr(b);
	
	cout << "ADD: " << dst << " = " << a << " + " << b << endl;

	cout << "ADD: " << int(*a_p + *b_p) << " = " << int(*a_p) << " + " << int(*b_p) << endl;
	*(dst_p) = ((*a_p) + (*b_p));
	//cout << "ADD RES = " << *dst_p << endl;
}

void asn() 
{
	char dst;
	char src;
	src = vars.top(); vars.pop();
	dst = vars.top(); vars.pop();

	unsigned char* dst_p;

	dst_p = addr(dst);

	(*dst_p) = src;
}

void end()
{
	cout << "end() called" << endl; 	
}

void exec(command cmd);

int N = 0;

int repc = 0;

void rep()
{
	repc++;
	int n;
	n = reps.top(); reps.pop();

	command cmd;
	vector<command> cmds;
	while(1)
	{
		cmd = read();
		N--;
		if(cmd == END)
		{
			break;
		}
		if(cmd == REP) {
			int i = 0;
			while(i < n) {
				cout << "\nEXEC REP #" << i << endl;
				exec(cmd);
				cout << "EXEC REP #" << i  << " done.\n"<< endl;
				i++;
			}
		}
		else {
			cmds.push_back(cmd);
		}	
	}
	cout << "\nREP BLOCK START" << endl;
	int j = 0;
	while(j < n)
	{
		cout << "rep # " << j << endl;
		int i = 0;
		while(i < cmds.size())
		{	
			cmd = cmds[i];
			cout << "cmd # " << i << endl;
		
			char dst  = -1;
			char arg1 = -1;
			char arg2 = -1;

			if(cmd == ADD) 
			{
				arg2 = vars.top();
				vars.pop();
				arg1 = vars.top(); 
				vars.pop();
				dst = vars.top();

				vars.push(arg1);
				vars.push(arg2);
			}
			else if(cmd == ASN)
			{
				arg1 = vars.top(); 
				vars.pop();
				dst = vars.top();

				vars.push(arg1);
			}
		
			exec(cmd);

			if(cmd == ADD)
			{
				vars.push(dst);
				vars.push(arg1);
				vars.push(arg2);
			}
			else if(cmd == ASN) 
			{
				vars.push(dst);
				vars.push(arg1);
			}

			i++;
			cout << "cmd # " << i << "done." << endl;
		}
		cout << "rep # " << j << "done. " << endl;
		j++;
	}
	cout << "REP BLOCK DONE\n" << endl;
}


void exec(command cmd)
{
	switch(cmd)
	{
		case ADD:			
			add();
			break;
		case ASN:
			asn();
			break;
		case REP:
			rep();
			break;
		case END:
			end();
			break;
	}
}

int main() 
{

	scanf("%d", &N);
	
	command cmd;
	string str;
	getline(cin, str);
	while(N--) 
	{
		cmd = read();
		exec(cmd);
	}
	printf("a = %d\nb = %d\nc = %d\nd = %d\ne = %d\nf = %d\ng = %d\n", a, b, c, d, e, f, g);
	
	cout << "addc = " << addc << endl;
	cout << "repc = " << repc << endl;
}
