#include "FazanDS.h"

FazanDataStructure::FazanDataStructure(std::istream& inp) {
	addWords(inp);
	generatePossibilityVector();
}

void FazanDataStructure::addWords(std::istream& fin) {
	noWords = 0;
	std::string tmp;

	while (fin) {
		fin >> tmp;
		MorphoAnalyzer::convertLwr(tmp);
		if (tmp.length() < 3) continue;
		try {
			mat[MorphoAnalyzer::prefixId(tmp)][MorphoAnalyzer::sufixId(tmp)].push_back(tmp);
			++noWords;
		}
		catch (...) {
			std::cerr << "\n  [-] Eroare cuvant invalid : " << tmp;
		}
	}
}

void FazanDataStructure::generatePossibilityVector() {
	for (size_t line = 0; line < 961; line++) {
		size_t count = 0;
		for (size_t col = 0; col < 961; col++) {
			count += mat[line][col].size();
		}
		possVector[line] = count;
	}
}

size_t FazanDataStructure::getNoWords() {
	return noWords;
}

std::pair<std::string, size_t> FazanDataStructure::suggestWord(const std::string& givenWord) {
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
std::vector<std::string>::iterator FazanDataStructure::find_word(const std::string& wordToFind)
{
	size_t prefix, sufix;
	prefix = MorphoAnalyzer::prefixId(wordToFind);
	sufix = MorphoAnalyzer::sufixId(wordToFind);

	return std::find(mat[prefix][sufix].begin(), mat[prefix][sufix].end(), wordToFind);
}

bool FazanDataStructure::checkWordExists(const std::string& wordToCheck) {
	size_t prefix, sufix;
	try {
		prefix = MorphoAnalyzer::prefixId(wordToCheck);
		sufix = MorphoAnalyzer::sufixId(wordToCheck);
		auto foundAt = find_word(wordToCheck);
		if (foundAt == mat[prefix][sufix].end()) return false;
	}
	catch (...) {
		return false;
	}

	return true;
}

//Does NOT check if word exists
void FazanDataStructure::deleteWord(const std::string& wordToDelete) {
	size_t prefix, sufix;
	prefix = MorphoAnalyzer::prefixId(wordToDelete);
	sufix = MorphoAnalyzer::sufixId(wordToDelete);

	auto foundAt = find_word(wordToDelete);
	mat[prefix][sufix].erase(foundAt);

	//Update number of words and possibility vector
	possVector[prefix]--;
	noWords--;
}

bool FazanDataStructure::checkBlockingWord(const std::string& wordToCheck){
	try {
		if (possVector[MorphoAnalyzer::sufixId(wordToCheck)] == 0) return true;
		return false;
	}
	catch (...) {
		return false;
	}

}

std::list<std::string> FazanDataStructure::getBlockingWords(size_t givenPrefixId){
	std::list<std::string> blockingWordsStartingWithGivenPrefixId;
	for (size_t col = 0; col < 961; col++) {
		if (mat[givenPrefixId][col].size() && checkBlockingWord(mat[givenPrefixId][col][0])) {
			for (auto& blockingWord : mat[givenPrefixId][col])
				blockingWordsStartingWithGivenPrefixId.push_back(blockingWord);
		}
	}

	return blockingWordsStartingWithGivenPrefixId;
}
