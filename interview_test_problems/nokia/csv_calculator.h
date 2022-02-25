#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

namespace nokia_test
{
    class csv_calculator
    {
        using csv_tree_t = std::unordered_map<std::string, std::unordered_map<int, std::string>>;
        
        enum class operation
        {
            ADD = '+',
            SUB = '-',
            MUL = '*',
            DIV = '/',
            NON = 0
        };

        csv_tree_t csv_tree;
        std::vector<std::string> columns;
        std::vector<int> rows;
        
        #ifdef DEBUG
        std::ostream& debug_output = std::cout;
        size_t calculate_cell_call_count = 0;
        #endif
        
        // PRINTS A TREE TO CSV
        void print_csv_tree(std::ostream& output, bool values);
        
        // EXTRACTS OPERANDS FROM GIVEN CELL
        // op_1 and op_2 must be empty
        operation extract_operands_and_operator(const std::string& cell, std::string& op_1, std::string& op_2);
        
        // EXECUTES GIVE OPERATION
        bool execute_operation(operation operation, int a, int b, int& result);
        
        #ifdef DEBUG
        int extract_operand(const std::string& operand, int operand_num);
        #else
        int extract_operand(const std::string& operand);
        #endif
        
        void validate_cell_content(const std::string& cell, const std::string& column, int row);
        std::string& extract_cell_content(const std::string& column, int row);
        // CALCULATES VALUE OF EXPRESSION IN A GIVEN CELL. 
        // RECURSIVLY CALCULATED NESTED CELLS
        int calculate_cell(const std::string& column, int row);
        
    	// READ INPUT BUILD TREE REPRESENTATION OF CSV
        void build_csv_tree(std::istream& in);
        
    	// SCAN CELLS AND CALCULATE EXPRESSIONS
        void process_csv_tree();
        
    public:

        void read_from(std::istream& input);
        
        void write_to(std::ostream& output);
        
    };
};
