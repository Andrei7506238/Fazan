#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include "MorphoAnalyzer.h"

class FazanDataStructure{
	size_t noWords;
	std::vector<std::string> mat[961][961];
	size_t possVector[961]{};

	void addWords(std::istream& fin);
	void generatePossibilityVector();

public:
	FazanDataStructure(std::istream& inp);
	std::pair<std::string, size_t> suggestWord(const std::string& givenWord);
	std::vector<std::string>::iterator find_word(const std::string& wordToFind);
	bool checkWordExists(const std::string& wordToCheck);
	void deleteWord(const std::string& wordToDelete);
	size_t getNoWords();

	bool checkBlockingWord(const std::string& wordToCheck);
	std::list<std::string> getBlockingWords(size_t givenPrefixId);
};

