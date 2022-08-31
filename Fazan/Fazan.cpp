#include "Fazan.h"

Fazan::Fazan(std::istream& inp) {
	addWords(inp);
	generatePossibilityVector();
}

void Fazan::addWords(std::istream& fin) {
	noWords = 0;
	std::string tmp;

	while (fin) {
		fin >> tmp;
		MorphoAnalyzer::convertLwr(tmp);
		if (tmp.length() < 3) continue;
		mat[MorphoAnalyzer::prefixId(tmp)][MorphoAnalyzer::sufixId(tmp)].push_back(tmp);
		++noWords;
	}
}

void Fazan::generatePossibilityVector() {
	for (size_t line = 0; line < 961; line++) {
		size_t count = 0;
		for (size_t col = 0; col < 961; col++) {
			count += mat[line][col].size();
		}
		possVector[line] = count;
	}
}

size_t Fazan::getNoWords() {
	return noWords;
}

std::pair<std::string, size_t> Fazan::suggestWord(const std::string& givenWord) {
	size_t pfxId = MorphoAnalyzer::sufixId(givenWord);
	size_t minVarId = 99999;
	for (size_t col = 0; col < 961; col++) {
		if (mat[pfxId][col].size()) {
			if (minVarId == 99999 || possVector[col] < possVector[minVarId])
				minVarId = col;
		}
	}

	if (minVarId == 99999) return { "", 99999 };
	return { mat[pfxId][minVarId][0], possVector[minVarId] };
}

//Might throw exception
std::vector<std::string>::iterator Fazan::find_word(const std::string& wordToFind)
{
	size_t prefix, sufix;
	prefix = MorphoAnalyzer::prefixId(wordToFind);
	sufix = MorphoAnalyzer::sufixId(wordToFind);

	return std::find(mat[prefix][sufix].begin(), mat[prefix][sufix].end(), wordToFind);
}

bool Fazan::checkWordExists(const std::string& wordToCheck) {
	size_t prefix, sufix;
	prefix = MorphoAnalyzer::prefixId(wordToCheck);
	sufix = MorphoAnalyzer::sufixId(wordToCheck);

	try {
		auto foundAt = find_word(wordToCheck);
		if (foundAt == mat[prefix][sufix].end()) return false;
	}
	catch (...) {
		return false;
	}

	return true;
}

//Does NOT check if word exists
void Fazan::deleteWord(const std::string& wordToDelete) {
	size_t prefix, sufix;
	prefix = MorphoAnalyzer::prefixId(wordToDelete);
	sufix = MorphoAnalyzer::sufixId(wordToDelete);

	auto foundAt = find_word(wordToDelete);
	mat[prefix][sufix].erase(foundAt);

	//Update number of words and possibility vector
	possVector[prefix]--;
	noWords--;
}

size_t Fazan::MorphoAnalyzer::charToNumMapper(char x) {
	if (x >= 'a' && x <= 'z') return x - 'a';
	if (x == '~') return 26;
	if (x == '^') return 27;
	if (x == '#') return 28;
	if (x == '.') return 29;
	if (x == ',') return 30;

	throw 999;
}

char Fazan::MorphoAnalyzer::numToCharMapper(size_t x) {
	if (x < 26) return 26 + 'a';
	if (x == 26) return '~';
	if (x == 27) return '^';
	if (x == 28) return '#';
	if (x == 29) return '.';
	if (x == 30) return ',';

	throw 999;
}

inline size_t Fazan::MorphoAnalyzer::groupConverter(const std::string& x) {
	return charToNumMapper(x[0]) * 31 + charToNumMapper(x[1]);
}

std::string Fazan::MorphoAnalyzer::groupInvConverter(size_t x) {
	std::string tmp;
	tmp += numToCharMapper(char(x / 31)) + numToCharMapper(char(x % 31));
	return tmp;
}

inline size_t Fazan::MorphoAnalyzer::prefixId(const std::string& x) {
	return groupConverter(x.substr(0, 2));
}

inline size_t Fazan::MorphoAnalyzer::sufixId(const std::string& x) {
	return groupConverter(x.substr(x.length() - 2, 2));
}

void Fazan::MorphoAnalyzer::convertLwr(std::string& x) {
	for (size_t i = 0; i < x.length(); i++)
		x[i] = tolower(x[i]);
}
