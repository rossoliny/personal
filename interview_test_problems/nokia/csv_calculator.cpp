#include "csv_calculator.h"

#include <sstream>

namespace nokia_test
{
	// PRINTS A TREE TO CSV
	void csv_calculator::print_csv_tree(std::ostream& output, bool values)
	{
		output << ',';
		for(int i = 0; i < columns.size(); ++i)
		{
			output << columns[i] << (i == columns.size() - 1 ? "" : ",");
		}
		output << '\n';
		for(auto row : rows)
		{
			output << row;
			for(auto column : columns)
			{
				if(values)
				{
					output << ',' << csv_tree[column][row];
				}
				else
				{
					output << ',' << (csv_tree[column][row][0] != '=');
				}
			}
			output << '\n';
		}
	}

	// EXTRACTS OPERANDS FROM GIVEN CELL
	// op_1 and op_2 must be empty
	csv_calculator::operation csv_calculator::extract_operands_and_operator(const std::string& cell, std::string& op_1, std::string& op_2)
	{
		#ifdef DEBUG
		debug_output << "extracting operands from: " << cell << std::endl;
		#endif
		
		for(int i = 1; i < cell.size(); ++i)
		{
			char ch = cell[i];
			switch(ch)
			{
				case '*':
				case '/':
				case '+':
					op_1 = cell.substr(1, i - 1);
					op_2 = cell.substr(i + 1, std::string::npos);
					return operation(ch);
				case '-':
					if(i == 1)
					{
						continue;
					}
					op_1 = cell.substr(1, i - 1);
					op_2 = cell.substr(i + 1, std::string::npos);
					return operation(ch);
			}
		}
		throw std::runtime_error("Invalid format in cell: " + cell);
		return operation::NON;
	}

	// EXECUTES GIVE OPERATION
	bool csv_calculator::execute_operation(operation operation, int a, int b, int& result)
	{
		switch(operation)
		{
			case operation::ADD:
				result = a + b;
				break;
			case operation::SUB:
				result = a - b;
				break;
			case operation::MUL:
				result = a * b;
				break;
			case operation::DIV:
				if(b == 0)
				{
					return false;
				}
				result = a / b;
				break;
			case operation::NON:
				return false;
		}
		return true;
	}

	
	#ifdef DEBUG
	int csv_calculator::extract_operand(const std::string& operand, int operand_num)
	#else
	int csv_calculator::extract_operand(const std::string& operand)
	#endif
	{
		int op_1_val = 0;
		if(std::isdigit(operand[0]) || operand[0] == '-')
		{
			// just parsing to int
			op_1_val = std::stoi(operand);
			#ifdef DEBUG
			debug_output << "operand " << operand_num << " is a number: " << op_1_val << std::endl;
			#endif
		}
		else
		{
			// operand_1 is a link
			// extract col and row of link
			int i = 0;
			std::string c;
			for(; i < operand.size(); ++i)
			{
				if(std::isdigit(operand[i]))
				{
					break;
				}
				c += operand[i];
			}

			std::string r;
			for(int j = i; j < operand.size(); ++j)
			{
				if(!std::isdigit(operand[j]) && operand[j] != '-')
				{
					throw std::runtime_error("Row " + operand.substr(i) + " is invalid, only numbers allowed");
				}
				else
				{
					r += operand[j];
				}
			}

			#ifdef DEBUG
			debug_output << "operand " << operand_num << " is a link: [" << c << "][" << r << "]" << std::endl;
			#endif
			// recursive calculation
			op_1_val = calculate_cell(c, std::stoi(r));
			#ifdef DEBUG
			debug_output << "\tafter recursive call to calculate link\n";
			debug_output << "\tcalculated value of a operand " << operand_num << ": " << op_1_val << '\n';
			#endif
		}
		return op_1_val;
	}

	void csv_calculator::validate_cell_content(const std::string& cell, const std::string& column, int row)
	{
		#ifdef DEBUG
		debug_output << "validating cell \'" << column << row << "\': " << cell << std::endl;
		#endif
		// if does not start with = or - then it must contain only digits

		int i = 0;
		if((cell[0] != '=' && cell[0] != '-') || cell[i++] == '-')
		{
			#ifdef DEBUG
			debug_output << "cell \'" << column << row << "\': " << cell << " is an expression"<< std::endl;
			#endif
			for(;i < cell.size(); ++i)
			{
				if(!std::isdigit(cell[i]))
				{
					throw std::runtime_error("Invalid format in cell \'" + column + std::to_string(row) + "\': " + cell);
				}
			}
		}
	}

	std::string& csv_calculator::extract_cell_content(const std::string& column, int row)
	{
		auto iter = csv_tree.find(column);
		if(iter == csv_tree.end())
		{
			throw std::runtime_error("Invalid column name in: " + column + std::to_string(row));
		}
		auto iter_2 = iter->second.find(row);
		if(iter_2 == iter->second.end())
		{
			throw std::runtime_error("Invalid row number in: " + column + std::to_string(row));
		}
		validate_cell_content(iter_2->second, column, row);
		return iter_2->second;
	}

	// CALCULATES VALUE OF EXPRESSION IN A GIVEN CELL. 
	// RECURSIVLY CALCULATED NESTED CELLS
	int csv_calculator::calculate_cell(const std::string& column, int row)
	{
		#ifdef DEBUG
		debug_output << "\ncell[" << column << "][" << row << "]: \'" << csv_tree[column][row] << "\'" << std::endl;
		#endif

		std::string& cell = extract_cell_content(column, row);

		#ifdef DEBUG
		debug_output << "call number: " << calculate_cell_call_count << std::endl;
		calculate_cell_call_count++;
		#endif
		
		// cell must be calculated
		if(cell[0] == '=')
		{
			#ifdef DEBUG
			debug_output << "cell must be calculated" << std::endl;
			#endif
			// string representation of first and second operands
			std::string op_1;
			std::string op_2;
			operation op;
		   // get operation and init operands;
			op = extract_operands_and_operator(cell, op_1, op_2);
			
			#ifdef DEBUG
			debug_output << "expression: " << op_1 << (char)op << op_2 << '\n';
			#endif
			
			// if operand_1 is a link -> extract col and row from link and recursive call and parse result to int
			// else just parse to int
			// if operand_2 is a link -> extract col and row from link and recursive call and parse result to int
			// else just parse to int
			#ifdef DEBUG
			int op_1_val = extract_operand(op_1, 1);
			int op_2_val = extract_operand(op_2, 2);
			#else
			int op_1_val = extract_operand(op_1);
			int op_2_val = extract_operand(op_2);
			#endif
			
		   // execute operation
			#ifdef DEBUG
			debug_output << "executing operation: " << op_1_val << (char)op << op_2_val << '\n';
			#endif
			
			int result;
			if(!execute_operation(op, op_1_val, op_2_val, result))
			{
				//std::cerr <<  << std::endl;
				throw std::runtime_error("Division by zero in cell \'" + column + std::to_string(row) +"\': " + op_1 + " / " + op_2);
			}
			// return result
			#ifdef DEBUG
			debug_output << "\texecution result: " << op_1_val << (char)op << op_2_val << '=' << result << '\n';
			debug_output << "done calculating cell[" << column << "][" << row << "]: \'" << cell << "\'" << std::endl;
			#endif
			cell = std::to_string(result);

			return result;
		}
		// cell is already calculated
		else
		{
			#ifdef DEBUG
			debug_output << "cell is already calculated: " << cell << std::endl;
			#endif
			return std::stoi(cell);
		}
	}

	void csv_calculator::build_csv_tree(std::istream& in)
	{
		#ifdef DEBUG
		debug_output << "START READING CSV" << std::endl;
		#endif

		std::string str_buf;
		
		std::string& header = str_buf;
		std::getline(in, header, '\n');
		
		std::istringstream columns_ss(header);
		std::string& column = str_buf;
		while(std::getline(columns_ss, column, ','))
		{
			if(!column.empty())
			{
				columns.push_back(std::move(column));
			}
			else if(column.find_first_not_of(' ') != std::string::npos)
			{
				throw std::runtime_error("Empty column name are not allowed");
			}
		}
		
		std::string& line = str_buf;
		while(std::getline(in, line, '\n'))
		{
			std::istringstream line_ss(line);
			std::string& row_str = str_buf;
			std::getline(line_ss, row_str, ','); 
			
			// check if row_str is a number
			for(auto ch : row_str)
			{
				if(!std::isdigit(ch) && ch != '-')
				{
					throw std::runtime_error("Row " + row_str + " is invalid, only numbers allowed");
				}
			}

			size_t row_i = std::stoi(row_str);
			rows.push_back(row_i);
			
			std::string val;
			size_t column_i = 0;
			while(column_i < columns.size())
			{
				std::getline(line_ss, val, ',');
				column = columns[column_i];

				// if not an expression the validate its a value
				validate_cell_content(val, column, row_i);
				csv_tree[column][row_i] = std::move(val);
				column_i++;
			}
		}
		// PRINT BUILT TREE TO CHECK IF REPRESENTATION IS CORRECT
		#ifdef DEBUG
		debug_output << "CHECK TREE OF INPUT CSV" << std::endl;
		print_csv_tree(debug_output, true);
		#endif
	}

	void csv_calculator::process_csv_tree()
	{
		#ifdef DEBUG
		debug_output << std::endl << "Start calculations\n" << std::endl;
		#endif
		// SCAN CELLS AND CALCULATE EXPRESSIONS
		for(auto row : rows)
		{
			for(auto column : columns)
			{
				std::string& cell_val = csv_tree[column][row];
				bool is_resolved = cell_val[0] != '=';
				
				if(!is_resolved)
				{
					// TODO: calculate
					calculate_cell(column, row);
				}
			}
		}
		
		#ifdef DEBUG
		debug_output << "Finished calculations.\nRecursive calls: " << calculate_cell_call_count << std::endl;
		debug_output << "\nResulting CSV" << '\n';
		#endif
	}

	void csv_calculator::read_from(std::istream& input)
	{
		// READ INPUT BUILD TREE REPRESENTATION OF CSV
		build_csv_tree(input);
	}

	void csv_calculator::write_to(std::ostream& output)
	{
		process_csv_tree();
		print_csv_tree(output, true);
	}

};