#include "csv_calculator.h"
#include <fstream>

#ifdef TEST
#include <csv_calculator_tests>
#endif    

void run_program(const char* file_path_str)
{
	try
	{
		std::ifstream csv_file(file_path_str);
		if(csv_file.fail()){
        	std::cout << "File not found: " << file_path_str << std::endl;
        	std::exit(-2);
    	}

	    nokia_test::csv_calculator csv_calculator;
	    csv_calculator.read_from(csv_file);
	    csv_calculator.write_to(std::cout);
	}
	catch(std::runtime_error re)
	{
		std::cout << re.what() << std::endl;
	}
	catch(std::invalid_argument ia)
	{
		std::cout << ia.what() << std::endl;
	}
}

int main(int argc, char** argv)
{
    #ifdef TEST
    run_tests();
    #else

    if(argc > 1)
    {
    	run_program(argv[1]);
    }
    else
    {
    	std::cout << "usage:\n" 
    					"\t$ csvreader.exe file.csv\n"
    					"\t - file.csv - input csv file from which to read data.\n";
    	return -1;
    }

    #endif
}

