#pragma once
#include <string>

class MorphoAnalyzer {
	static size_t charToNumMapper(wchar_t x);
	static wchar_t numToCharMapper(size_t x);

public:
	static size_t groupConverter(const std::wstring& x);
	static std::wstring groupInvConverter(size_t x);
	static size_t prefixId(const std::wstring& x);
	static size_t sufixId(const std::wstring& x);

	static void convertLwr(std::wstring& x);
};
