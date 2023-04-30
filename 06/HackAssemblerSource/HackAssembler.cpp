#include <unordered_map>
#include <fstream>

#include "Parser.hpp"
#include "CodeModule.hpp"


void load_default_symbols(std::unordered_map<std::string, int>& symbol_table)
{
	for (int i = 0; i < 16; i++) symbol_table["R" + std::to_string(i)] = i;

	symbol_table["SP"] 		= 0;
	symbol_table["LCL"] 	= 1;
	symbol_table["ARG"] 	= 2;
	symbol_table["THIS"] 	= 3;
	symbol_table["THAT"] 	= 4;

	symbol_table["SCREEN"] 	= 16384;
	symbol_table["KBD"] 	= 24576;
}

std::string int2bin(int n)
{
	std::string res = "0000000000000000";

	for (int i = 0; i < 15; i++)
	{
		int mask = 1 << i;
		int d = n & mask;
		res[14 - i] = '0' + (d > 0);
	}

	return res;
}

bool is_number(std::string str)
{
	for (char ch : str) if (ch < '0' || ch > '9') return false;

	return true;
}


int main(int argc, const char * argv[])
{
	// Load arguments
	if (argc != 2) std::cout << "INVALID ARGUMENT" << std::endl;
	Parser parser(argv[1]);

	// Setup output
	std::string output_name(argv[1]);
	output_name = output_name.substr(0, output_name.size() - 3) + "hack";
	std::ofstream output(output_name);

	// Setup the symbol table
	std::unordered_map<std::string, int> symbol_table;
	load_default_symbols(symbol_table);

	// Setup counters
	int variable_counter = 0;
	int line_number = 0;

	// First pass
	while (parser.hasMoreLines())
	{
		parser.advance();
		Type type = parser.instructionType();
		
		if (type == Type::L_INSTRUCTION)
		{
			std::string symbol = parser.symbol();

			symbol_table[symbol] = line_number;
		}
		else if (type == Type::A_INSTRUCTION) line_number++;
		else if (type == Type::C_INSTRUCTION) line_number++;
	}

	// Second pass
	parser.reset();
	while (parser.hasMoreLines())
	{
		parser.advance();
		Type type = parser.instructionType();

		// @xxx
		if (type == Type::A_INSTRUCTION)
		{
			std::string symbol = parser.symbol();
			int address = 0;

			if (is_number(symbol)) address = std::stoi(symbol);
			else
			{
				if (!symbol_table.contains(symbol)) 
				{
					symbol_table[symbol] = 16 + variable_counter;
					variable_counter++;
				}

				address = symbol_table[symbol];
			}

			std::string machine_code = int2bin(address);

			output << machine_code << std::endl;
		}
		// dest=comp;jump
		else if (type == Type::C_INSTRUCTION)
		{
			std::string machine_code = "111" + CodeModule::comp(parser.comp()) + CodeModule::dest(parser.dest()) + CodeModule::jump(parser.jump());

			output << machine_code << std::endl;
		}
	}


	// Terminate
	parser.close();
	output.close();

	return 1;
}