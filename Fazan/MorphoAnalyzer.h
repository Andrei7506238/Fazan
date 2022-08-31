#pragma once
#include <string>

class MorphoAnalyzer {
	static size_t charToNumMapper(char x);
	static char numToCharMapper(size_t x);

public:
	static size_t groupConverter(const std::string& x);
	static std::string groupInvConverter(size_t x);
	static size_t prefixId(const std::string& x);
	static size_t sufixId(const std::string& x);

	static void convertLwr(std::string& x);
};
