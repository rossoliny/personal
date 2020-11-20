#include <iostream>
#include <string>
#include <cctype>
#include <map>

enum Token_value 
{
	NAME, NUMBER, END,
	PLUS = '+', MINUS = '-', MUL = '*', DIV = '/',
	PRINT = ';', ASSIGN = '=', LP = '(', RP = ')'
};

Token_value curr_tok = PRINT;
std::map<std::string, double> table;
double number_value;
std::string string_value;
int no_of_errors = 0;

double expr(bool);

int error(const std::string& msg) 
{
	no_of_errors++;
	std::cerr << "error: " << msg << '\n';
	return 1;
}

Token_value get_token() 
{
	char ch;
	do {
		if(!std::cin.get(ch)) {
			return curr_tok = END;
		}
	} while(ch != '\n' && isspace(ch));

	switch(ch) {
	case 0:
		return curr_tok = END;
	case ';':
	case '\n':
		return curr_tok = PRINT;
	case '*':
	case '/':
	case '+':
	case '-':
	case '(':
	case ')':
	case '=':
		return curr_tok = Token_value(ch);
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '.':
		std::cin.putback(ch);
		std::cin >> number_value;
		return curr_tok = NUMBER;
	default:
		if(isalpha(ch)) {
			string_value = ch;
			while(std::cin.get(ch) && isalnum(ch)) {
				string_value.push_back(ch);
			}
			std::cin.putback(ch);
			return curr_tok = NAME;
		}
		error("invalid token");
		return curr_tok = PRINT;
	}
}

double prim(bool get) 
{
	if(get) {
		get_token();
	}

	switch(curr_tok) {
	case NUMBER:
	{
		double v = number_value;
		get_token();
		return v;
	}
	case NAME:
	{
		double& v = table[string_value];
		if(get_token() == ASSIGN) {
			v = expr(true);
		}
		return v;
	}
	case MINUS: // unary
	{
		return -prim(true);
	}
	case LP:
	{
		double e = expr(true);
		if(curr_tok != RP) {
			return error("expected ')'");
		}
		get_token();
		return e;
	}
	default:
	{
		return error("expected primary expression");
	}
	}
}

double term(bool get) 
{
	double left = prim(get);

	for(;;) {
		switch(curr_tok) {
		case MUL:
		{
			left *= prim(true);
			break;
		}
		case DIV:
		{
			if(double d = prim(true)) {
				left /= prim(true);
				break;
			}
			return error("division by 0");
		}
		default:
		{
			return left;
		}
		}
	}
}

double expr(bool get) 
{
	double left = term(get);

	for(;;) {
		switch(curr_tok) {
		case PLUS:
		{
			left += term(true);
			break;
		}
		case MINUS:
		{
			left -= term(true);
			break;
		}
		default:
		{
			return left;
		}
		}
	}
}



int main(int argc, char* argv[]) 
{
	table["pi"] = 3.1415;
	table[ "e"] = 2.7182;

	std::cout << "lol\n";
	std::cout << "lol\n";
	std::cout << "lol\n";
	std::cout << "lol\n";
	std::cout << "lol\n";
	while(std::cin) {
		get_token();
		if(curr_tok == END) {
			break;
		}
		if(curr_tok == PRINT) {
			continue;
		}
		std::cout << expr(false) << '\n';
	}
	return no_of_errors;
}