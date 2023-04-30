#ifndef CODEMODULE_hpp
#define CODEMODULE_hpp

#include <string>
#include <unordered_map>

#include "CodeModule.hpp"

class CodeModule
{
public:
	static std::string dest(const std::string& d);
	static std::string comp(const std::string& c);
	static std::string jump(const std::string& j);

private:
	CodeModule();

	static std::unordered_map<std::string, std::string> map_dest;
	static std::unordered_map<std::string, std::string> map_comp;
	static std::unordered_map<std::string, std::string> map_jump;
};

std::string CodeModule::dest(const std::string& d)
{
	if (map_dest.contains(d)) return map_dest[d];

	return "000";
}

std::string CodeModule::comp(const std::string& c)
{
	if (map_comp.contains(c)) return map_comp[c];

	return "0000000";
}

std::string CodeModule::jump(const std::string& j)
{
	if (map_jump.contains(j)) return map_jump[j];

	return "000";
}

std::unordered_map<std::string, std::string> CodeModule::map_dest = {
	{"", 	"000"},
	{"M", 	"001"},
	{"D", 	"010"},
	{"DM", 	"011"},
	{"MD", 	"011"},
	{"A", 	"100"},
	{"AM", 	"101"},
	{"MA", 	"101"},
	{"AD", 	"110"},
	{"DA", 	"110"},
	{"ADM", "111"},
	{"AMD", "111"},
	{"DAM", "111"},
	{"DMA", "111"},
	{"MAD", "111"},
	{"MDA", "111"},
};
std::unordered_map<std::string, std::string> CodeModule::map_comp = {
	{"0", 	"0101010"},
	{"1", 	"0111111"},
	{"-1", 	"0111010"},
	{"D", 	"0001100"},
	{"A", 	"0110000"},
	{"!D", 	"0001101"},
	{"!A", 	"0110001"},
	{"-D", 	"0001111"},
	{"-A", 	"0110011"},
	{"D+1",	"0011111"},
	{"A+1", "0110111"},
	{"D-1", "0001110"},
	{"A-1", "0110010"},
	{"D+A", "0000010"},
	{"A+D", "0000010"},
	{"D-A", "0010011"},
	{"A-D", "0000111"},
	{"D&A", "0000000"},
	{"A&D", "0000000"},
	{"D|A", "0010101"},
	{"A|D", "0010101"},
	{"M", 	"1110000"},
	{"!M", 	"1110001"},
	{"-M", 	"1110011"},
	{"M+1", "1110111"},
	{"M-1", "1110010"},
	{"D+M", "1000010"},
	{"M+D", "1000010"},
	{"D-M", "1010011"},
	{"M-D", "1000111"},
	{"D&M", "1000000"},
	{"M&D", "1000000"},
	{"D|M", "1010101"},
	{"M|D", "1010101"}
};
std::unordered_map<std::string, std::string> CodeModule::map_jump = {
	{"", 	"000"},
	{"JGT", "001"},
	{"JEQ", "010"},
	{"JGE", "011"},
	{"JLT", "100"},
	{"JNE", "101"},
	{"JLE", "110"},
	{"JMP", "111"},
};

#endif