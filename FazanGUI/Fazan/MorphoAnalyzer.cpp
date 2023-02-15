#include "MorphoAnalyzer.h"

size_t MorphoAnalyzer::charToNumMapper(char x) {
	if (x >= 'a' && x <= 'z') return x - 'a';
	if (x == '~') return 26;
	if (x == '^') return 27;
	if (x == '#') return 28;
	if (x == '.') return 29;
	if (x == ',') return 30;

	throw 999;
}

char MorphoAnalyzer::numToCharMapper(size_t x) {
	if (x < 26) return x + 'a';
	if (x == 26) return '~';
	if (x == 27) return '^';
	if (x == 28) return '#';
	if (x == 29) return '.';
	if (x == 30) return ',';

	throw 999;
}

size_t MorphoAnalyzer::groupConverter(const std::string& x) {
	return charToNumMapper(x[0]) * 31 + charToNumMapper(x[1]);
}

std::string MorphoAnalyzer::groupInvConverter(size_t x) {
	std::string tmp;
	tmp += numToCharMapper(char(x / 31));
	tmp += numToCharMapper(char(x % 31));
	return tmp;
}

size_t MorphoAnalyzer::prefixId(const std::string& x) {
	return groupConverter(x.substr(0, 2));
}

size_t MorphoAnalyzer::sufixId(const std::string& x) {
	return groupConverter(x.substr(x.length() - 2, 2));
}

void MorphoAnalyzer::convertLwr(std::string& x) {
	for (size_t i = 0; i < x.length(); i++)
		x[i] = tolower(x[i]);
}
