#pragma once
#include <string>
#include <map>

namespace Lexer 
{
	enum Token_value
	{
	      NAME,		NUMBER,		END,
	      PLUS='+',	MINUS='-',		MUL='*',		DIV='/',
	      PRINT=';',	ASSIGN='=',		LP='(',		RP=')',
	};

	Token_value curr_tok = PRINT;
	double number_value;
	std::string string_value;
	std::map<std::string, double> table;

	Token_value get_token();
}