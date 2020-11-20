#include "Lexer.h"
#include "Error.h"
#include <cctype>
#include <iostream>
#include <string>

Lexer::Token_value Lexer::get_token() 
{
	using Error::error;
	
	char ch = 0;
	do { 
		if(!std::cin.get(ch)) {
			return curr_tok = END;		// skip whitespace except '\n'
		}
	} while (ch != '\n' && isspace(ch));
	
	switch (ch) {
		case 0 :
		    return curr_tok = END;
		case ';' :
		case '\n' :
		    return curr_tok = PRINT;
		case '*' :
		case '/' :
		case '+' :
		case '-' :
		case '(' :
		case ')' :
		case '=' :
		    return curr_tok = Token_value(ch);

		case '0' :	case '1' :	case '2' :	case '3' : 	case '4' :
		case '5' :	case '6' :	case '7' :	case '8' :	case '9' :
		case '.' :
		    std::cin.putback(ch);
		    std::cin >> number_value;
		    return curr_tok = NUMBER;
		default:				// NAME, NAME =, or error
		    if (isalpha(ch)) {
			    string_value = ch;
			    while (std::cin.get(ch) && isalnum(ch)) {
			    	string_value.push_back(ch);
			    }
			    std::cin.putback(ch);
			    return curr_tok = NAME;
		    }
		    error("Bad Token");
		    return curr_tok = PRINT;
	}
}