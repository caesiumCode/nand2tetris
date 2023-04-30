#ifndef PARSER_hpp
#define PARSER_hpp

#include "Parser.hpp"

#include <iostream>
#include <fstream>
#include <string>

enum Type
{
	A_INSTRUCTION,
	C_INSTRUCTION,
	L_INSTRUCTION,
	U_INSTRUCTION // Unknown instruction
};

class Parser
{
public:
	Parser(const std::string& source);

	bool hasMoreLines();
	void advance();

	Type 		instructionType();
	std::string symbol();
	std::string dest();
	std::string comp();
	std::string jump();

	std::string command();

	void reset();
	void close();

private:
	std::ifstream stream;
	std::string current_line;

	bool isInstruction();
	bool legalChar(char ch);
};

#endif