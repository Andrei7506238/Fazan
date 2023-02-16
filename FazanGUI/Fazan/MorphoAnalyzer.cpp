#include "MorphoAnalyzer.h"

size_t MorphoAnalyzer::charToNumMapper(wchar_t x) {
	if (x >= L'a' && x <= L'z') return x - 'a';
	if (x == L'\u0103') return 26;
	if (x == L'\u00EE') return 27;
	if (x == L'\u00E2') return 28;
	if (x == L'\u0219') return 29;
	if (x == L'\u021B') return 30;

	throw std::exception("Exception: Unknown character");
}

wchar_t MorphoAnalyzer::numToCharMapper(size_t x) {
	if (x < 26) return x + 'a';
	if (x == 26) return '\u0103';
	if (x == 27) return '\u00EE';
	if (x == 28) return '\u00E2';
	if (x == 29) return '\u0219';
	if (x == 30) return '\u021B';

	throw std::exception("Exception: Unknown id");
}

size_t MorphoAnalyzer::groupConverter(const std::wstring& x) {
	return charToNumMapper(x[0]) * 31 + charToNumMapper(x[1]);
}

std::wstring MorphoAnalyzer::groupInvConverter(size_t x) {
	std::wstring tmp;
	tmp += numToCharMapper(wchar_t(x / 31));
	tmp += numToCharMapper(wchar_t(x % 31));
	return tmp;
}

size_t MorphoAnalyzer::prefixId(const std::wstring& x) {
	return groupConverter(x.substr(0, 2));
}

size_t MorphoAnalyzer::sufixId(const std::wstring& x) {
	return groupConverter(x.substr(x.length() - 2, 2));
}

void MorphoAnalyzer::convertLwr(std::wstring& x) {
	for (size_t i = 0; i < x.length(); i++)
		x[i] = tolower(x[i]);
}
