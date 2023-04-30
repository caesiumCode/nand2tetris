#include "Parser.hpp"

Parser::Parser(const std::string& source)
{
	stream.open(source);

	current_line = "";
}

bool Parser::hasMoreLines()
{
	return !stream.eof();
}

void Parser::advance()
{
	std::getline(stream, current_line);

	while (!isInstruction() && !stream.eof()) std::getline(stream, current_line);

	if (!stream.eof())
	{
		int i = 0;
		int instr_size = 0;
		while (!legalChar(current_line[i])) i++;
		while (i + instr_size < current_line.size() && legalChar(current_line[i + instr_size])) instr_size++;

		current_line = current_line.substr(i, instr_size);
	}
}

bool Parser::legalChar(char ch)
{
	if (ch >= 'a' && ch <= 'z') return true;
	if (ch >= 'A' && ch <= 'Z') return true;
	if (ch >= '0' && ch <= '9') return true;
	if (ch == '(' || ch == ')' || ch == '@' || ch == '=' || ch == ';') return true;
	if (ch == '-' || ch == '!' || ch == '+' || ch == '|' || ch == '&') return true;
	if (ch == '_' || ch == '.' || ch == ':' || ch == '$') return true;

	return false;
}

bool Parser::isInstruction()
{
	int i = 0;
	while (i < current_line.size() && current_line[i] == ' ') i++;

	if (i == current_line.size() || current_line[i] == '/') return false;
	else return legalChar(current_line[i]);
}

Type Parser::instructionType()
{
	if 		(current_line[0] == '@') 	return Type::A_INSTRUCTION;
	else if (current_line[0] == '(') 	return Type::L_INSTRUCTION;
	else if (!current_line.empty())		return Type::C_INSTRUCTION;
	else 								return Type::U_INSTRUCTION;
}

std::string Parser::symbol()
{
	int symbol_size = 0;
	for (int i = 1; i < current_line.size() && current_line[i] != ')'; i++) symbol_size++;

	return current_line.substr(1, symbol_size);
}

std::string Parser::dest()
{
	int dest_size = current_line.find("=");

	if (dest_size == std::string::npos) 	return "";
	else 									return current_line.substr(0, dest_size);
}

std::string Parser::comp()
{
	int eq_pos = current_line.find("=");
	int endcomp_pos = current_line.find(";");

	if (eq_pos == std::string::npos) eq_pos = -1;

	return current_line.substr(eq_pos+1, endcomp_pos - eq_pos - 1);
}

std::string Parser::jump()
{
	int endcomp_pos = current_line.find(";");

	if (endcomp_pos == std::string::npos) return "";
	else return current_line.substr(endcomp_pos+1);
}

std::string Parser::command()
{
	return current_line;
}

void Parser::reset()
{
	stream.clear();
	stream.seekg(0, std::ios::beg);

	current_line = "";
}

void Parser::close()
{
	stream.close();
}