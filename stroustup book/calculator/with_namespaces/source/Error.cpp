#include "Error.h"
#include <iostream>
double Error::error(const std::string& s)
{
      no_of_errors++;
      std::cerr << "error : " << s << '\n';
      return 1;
}