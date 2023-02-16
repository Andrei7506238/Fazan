#include "FazanDS.h"

FazanDataStructure::FazanDataStructure(std::wistream& inp, const std::list<std::wregex>& ignoreList) {
	addWords(inp, ignoreList);
	generateNONSV();
}

void FazanDataStructure::addWords(std::wistream& fin, const std::list<std::wregex>& ignoreList) {
	noWords = 0;
	std::wstring tmp;

	while (fin) {
		fin >> tmp;
		MorphoAnalyzer::convertLwr(tmp);
		if (tmp.length() < 3) continue;

		bool isAcceptedWord = true;
		for (const auto& regx : ignoreList)
			if(std::regex_match(tmp, regx))
			{
				isAcceptedWord = false;
				break;
			}
		if(!isAcceptedWord)
			continue;

		try {
			mat[MorphoAnalyzer::prefixId(tmp)][MorphoAnalyzer::sufixId(tmp)].push_back(tmp);
			++noWords;
		}
		catch (...) {
			//std::cerr << "\n  [-] Eroare cuvant invalid : " << tmp;
		}
	}
}

void FazanDataStructure::generateNONSV() {
	for (size_t line = 0; line < MLCGS; line++) {
		size_t count = 0;
		for (size_t col = 0; col < MLCGS; col++) {
			count += mat[line][col].size();
		}
		numberOfNodeSuccessorsVec[line] = count;
	}
}

size_t FazanDataStructure::getNoWords() {
	return noWords;
}

std::pair<std::wstring, size_t> FazanDataStructure::suggestWord(const std::wstring& givenWord) {
	size_t pfxId = MorphoAnalyzer::sufixId(givenWord);
	size_t minVarId = 99999;
	for (size_t col = 0; col < MLCGS; col++) {
		if (mat[pfxId][col].size()) {
			if (minVarId == 99999 || numberOfNodeSuccessorsVec[col] < numberOfNodeSuccessorsVec[minVarId])
				minVarId = col;
		}
	}

	if (minVarId == 99999) return { std::wstring(), 99999};
	return { mat[pfxId][minVarId][0], numberOfNodeSuccessorsVec[minVarId] };
}

//Might throw exception
std::vector<std::wstring>::iterator FazanDataStructure::findWord(const std::wstring& wordToFind)
{
	size_t prefix, sufix;
	prefix = MorphoAnalyzer::prefixId(wordToFind);
	sufix = MorphoAnalyzer::sufixId(wordToFind);

	return std::find(mat[prefix][sufix].begin(), mat[prefix][sufix].end(), wordToFind);
}

bool FazanDataStructure::checkWordExists(const std::wstring& wordToCheck) {
	size_t prefix, sufix;
	try {
		prefix = MorphoAnalyzer::prefixId(wordToCheck);
		sufix = MorphoAnalyzer::sufixId(wordToCheck);
		auto foundAt = findWord(wordToCheck);
		if (foundAt == mat[prefix][sufix].end()) return false;
	}
	catch (...) {
		return false;
	}

	return true;
}

void FazanDataStructure::deleteWord(const std::wstring& wordToDelete) {
	size_t prefix, sufix;
	prefix = MorphoAnalyzer::prefixId(wordToDelete);
	sufix = MorphoAnalyzer::sufixId(wordToDelete);

	auto foundAt = findWord(wordToDelete);
	mat[prefix][sufix].erase(foundAt);

	//Update number of words and possibility vector
	numberOfNodeSuccessorsVec[prefix]--;
	noWords--;
}

bool FazanDataStructure::checkBlockingWord(const std::wstring& wordToCheck) {
	try {
		if (numberOfNodeSuccessorsVec[MorphoAnalyzer::sufixId(wordToCheck)] == 0) return true;
		return false;
	}
	catch (...) {
		return false;
	}

}

std::list<std::wstring> FazanDataStructure::getBlockingWords(size_t givenPrefixId) {
	std::list<std::wstring> blockingWordsStartingWithGivenPrefixId;
	for (size_t col = 0; col < MLCGS; col++) {
		if (mat[givenPrefixId][col].size() && checkBlockingWord(mat[givenPrefixId][col][0])) {
			for (auto& blockingWord : mat[givenPrefixId][col])
				blockingWordsStartingWithGivenPrefixId.push_back(blockingWord);
		}
	}

	return blockingWordsStartingWithGivenPrefixId;
}

std::wstring FazanDataStructure::getMaxWordWithPrefix(int givenPrefix) {
	size_t mx_value = 0;
	size_t mx_pos = 0;

	if (givenPrefix == -1) {
		for (int swpfx = 1; swpfx < MLCGS; ++swpfx) {
			if (numberOfNodeSuccessorsVec[swpfx] > mx_value) {
				mx_value = numberOfNodeSuccessorsVec[swpfx];
				mx_pos = swpfx;
			}
		}

		givenPrefix = mx_pos;
		mx_pos = 0;
		mx_value = 0;
	}

	for (int nwpfx = 1; nwpfx < MLCGS; ++nwpfx) {
		if (numberOfNodeSuccessorsVec[nwpfx] > mx_value) {
			if (mat[givenPrefix][nwpfx].size() > 0) {
				mx_pos = nwpfx;
				mx_value = numberOfNodeSuccessorsVec[mx_pos];
			}
		}
	}

	if (mx_value == 0) return {};
	return mat[givenPrefix][mx_pos][0];
}