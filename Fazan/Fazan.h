#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <utility>

class Fazan{
	size_t noWords;
	std::vector<std::string> mat[961][961];
	size_t possVector[961]{};

	void addWords(std::istream& fin);
	void generatePossibilityVector();

	class MorphoAnalyzer {
		static inline size_t charToNumMapper(char x);
		static inline char numToCharMapper(size_t x);

	public:
		static inline size_t groupConverter(const std::string& x);
		static inline std::string groupInvConverter(size_t x);
		static inline size_t prefixId(const std::string& x);
		static inline size_t sufixId(const std::string& x);

		static void convertLwr(std::string& x);
	};

public:
	Fazan(std::istream& inp);
	std::pair<std::string, size_t> suggestWord(const std::string& givenWord);
	bool deleteWord(const std::string& wordToDelete);

	size_t getNoWords();
};

