#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <regex>
#include "MorphoAnalyzer.h"

class FazanDataStructure {
public:
	//Max Language Character Group Size (number of characters in alphabet squared)
	static const size_t MLCGS = 961;
private:
	//Lenght of total words in dictionary
	size_t noWords;
	//Vector of words for every combination of prefix and sufix
	std::vector<std::wstring> mat[MLCGS][MLCGS];
	//How many possible word are starting with a given prefix
	size_t numberOfNodeSuccessorsVec[MLCGS]{};					

	//Enter words in dictionary from a given input stream
	void addWords(std::wistream& fin, const std::list<std::wregex>& ignoreList);

	//Generate the vector of possible of number of node successors
	void generateNONSV();

public:
	FazanDataStructure(std::wistream& inp, const std::list<std::wregex>& ignoreList = {});

	//Calculate the best word in order to give the opponent the minumum number of possibilities. Returns word and possibilities of opponent
	std::pair<std::wstring, size_t> suggestWord(const std::wstring& givenWord);
	
	//Get iterator to a certain word
	std::vector<std::wstring>::iterator findWord(const std::wstring& wordToFind);
	
	//Check if a word exists
	bool checkWordExists(const std::wstring& wordToCheck);
	
	//Delete a word from dictionary, updating possVector and noWords. Does NOT check if word exists
	void deleteWord(const std::wstring& wordToDelete);

	//Getter for noWords
	size_t getNoWords();

	//Check if a word can be used for blocking
	bool checkBlockingWord(const std::wstring& wordToCheck);

	//Get a list of words used for blocking with a given prefix id
	std::list<std::wstring> getBlockingWords(size_t givenPrefixId);

	//Get the word with the most possibilities to continue the chain with a given prefix
	std::wstring getMaxWordWithPrefix(int givenPrefix = -1);
};