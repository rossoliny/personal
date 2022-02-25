#include "csv_calculator.h"

#include <iostream>
#include <string>
#include <sstream>

static std::ostream& test_output = std::cout;

#define ASSERT_EQUAL(a, b) (verify_test_case_result((a), (b)));

void verify_test_case_result(const std::string& a, const std::string& b)
{
    static int test_case_num = 1;

    if(a != b)
    {
        test_output << "TEST #" << test_case_num << " FAILED\n";
        test_output << "FIRST\n" << a << "\nIS NOT EQUAL TO\n" << b << std::endl;
    }
    else
    {
        test_output << "TEST #" << test_case_num << " PASSED" << std::endl;
    }
    test_case_num++;
}



// TESTS

void TEST_1()
{
    std::istringstream input(   ",A,B,Cell\n"
                                "1,=A2+Cell1,=Cell30-Cell30,=B1-1\n"
                                "2,=Cell30-3,=A1+Cell30,0\n"
                                "30,=B30-B30,=B1+A1,=10/2\n"
                            );
    
    std::string expected_output( ",A,B,Cell\n"
                                        "1,1,0,-1\n"
                                        "2,2,6,0\n"
                                        "30,0,1,5\n"
                                    );
    
    std::ostringstream actual_output;
    
    nokia_test::csv_calculator csv_calculator;
    csv_calculator.read_from(input);
    csv_calculator.write_to(actual_output);
    ASSERT_EQUAL(actual_output.str(), expected_output);
}

void TEST_2()
{
    std::istringstream input(   ",A,B,Cell\n"
                                "1,=A2+Cell1,=Cell30-Cell30,=B1-1\n"
                                "2,=Cell30-3,=A1+Cell30,0\n"
                                "30,=B30-B30,=B1+A1,=10/0\n"
                            );
    
    std::string expected_output("Division by zero in cell \'Cell30\': 10 / 0");
    
    try
    { 
        std::ostringstream actual_output;
        nokia_test::csv_calculator csv_calculator;
        csv_calculator.read_from(input);
        csv_calculator.write_to(actual_output);
    }
    catch(std::runtime_error e)
    {
        ASSERT_EQUAL(e.what(), expected_output);
    }
    
}

void TEST_3()
{
    std::istringstream input(   ",A,B,Cell\n"
                                "1,=A2+Cell1,=Cell30-Cell30,=B1-1\n"
                                "2,=Cell30-3,=A1+Cell30,0\n"
                                "30,=B30-B30,=B1+A1,=10/2\n"
                                "-1,-1,2,-2-3\n"
                            );
    
    std::string expected_output("Invalid format in cell \'Cell-1\': -2-3");
    
    try
    { 
        std::ostringstream actual_output;
        nokia_test::csv_calculator csv_calculator;
        csv_calculator.read_from(input);
        csv_calculator.write_to(actual_output);
    }
    catch(std::runtime_error e)
    {
        ASSERT_EQUAL(e.what(), expected_output);
    }
}


void run_tests()
{
    TEST_1();
    TEST_2();
    TEST_3();
}

int main()
{
	run_tests();
}

