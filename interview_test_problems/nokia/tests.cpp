#include "csv_calculator.h"

#include <iostream>
#include <string>
#include <sstream>

// TESTS

static std::ostream& test_output = std::cout;
#define ASSERT_EQUAL(a, b) (verify_test_case_result((a), (b)));

void verify_test_case_result(const std::ostringstream& a, const std::ostringstream& b)
{
    static int test_case_num = 1;
    std::string str_a = a.str();
    std::string str_b = b.str();
    if(str_a != str_b)
    {
        test_output << "TEST #" << test_case_num << " FAILED\n";
        test_output << "FIRST\n" << str_a << "\nIS NOT EQUAL TO\n" << str_b << std::endl;
    }
    else
    {
        test_output << "TEST #" << test_case_num << " PASSED" << std::endl;
    }
    test_case_num++;
}

void TEST_1()
{
    std::istringstream input(   ",A,B,Cell\n"
                                "1,=A2+Cell1,=Cell30-Cell30,=B1-1\n"
                                "2,=Cell30-3,=A1+Cell30,0\n"
                                "30,=B30-B30,=B1+A1,=10/2\n"
                            );
    
    std::ostringstream expected_output( ",A,B,Cell\n"
                                        "1,1,0,-1\n"
                                        "2,2,6,0\n"
                                        "30,0,1,5\n"
                                    );
    
    std::ostringstream actual_output;
    
    nokia_test::csv_calculator csv_calculator;
    csv_calculator.read_from(input);
    csv_calculator.write_to(actual_output);
    ASSERT_EQUAL(actual_output, expected_output);
}

void TEST_2()
{
    std::istringstream input(   ",A,B,Cell\n"
                                "1,=A2+Cell1,=Cell30-Cell30,=B1-1\n"
                                "2,=Cell30-3,=A1+Cell30,0\n"
                                "30,=B30-B30,=B1+A1,=10/0\n"
                            );
    
    std::ostringstream expected_output("Division by zero in cell \'Cell30\': =10/0\n");
    
    std::ostringstream actual_output;
    
    nokia_test::csv_calculator csv_calculator;
    csv_calculator.read_from(input);
    csv_calculator.write_to(actual_output);
    ASSERT_EQUAL(actual_output, expected_output);
}

void run_tests()
{
    TEST_1();
    TEST_2();
}

int main()
{
	run_tests();
}

