#pragma once
#include "Error.h"
#include "Lexer.h"

namespace Parser 
{
	double expr(bool get);
	double term(bool get);
	double prim(bool get);

	using namespace Lexer;
	using namespace Error;
}


