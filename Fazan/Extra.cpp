#include "Extra.h"

void Extra::generateBlockingWords(FazanDataStructure* x) {
	size_t countBlockingWords = 0;
	std::ofstream out("blockingWords.txt");
	if (!out.good()) {
		std::cerr << "[-] EROARE : Fisierul \"blockingWords.txt\" nu a putut fi deschis pentru scriere";
		exit(1);
	}

	for (size_t line = 0; line < FazanDataStructure::MLCGS; line++) {
		out << "\n " << MorphoAnalyzer::groupInvConverter(line) << "\t";
		auto lst = x->getBlockingWords(line);
		countBlockingWords += lst.size();

		for (auto& blockingWord : lst)
			out << blockingWord << " ";
	}

	std::cout << "Fisier \"blockingWords.txt\" generat. Numar cuvinte fazan : " << countBlockingWords;
	out.close();
}

void Extra::generateLongPath(FazanDataStructure* x) {
	std::ofstream out("longPath.txt");
	if (!out.good()) {
		std::cerr << "[-] EROARE : Fisierul \"longestChain.txt\" nu a putut fi deschis pentru scriere";
		exit(1);
	}
	
	size_t countChainWords = 0;

	std::string bestWord = x->getMaxWordWithPrefix();
	while (bestWord.length() > 0) {
		out << bestWord << std::endl;
		++countChainWords;
		x->deleteWord(bestWord);
		bestWord = x->getMaxWordWithPrefix(MorphoAnalyzer::sufixId(bestWord));
	}

	std::cout << "Fisier \"longPath.txt\" generat. Numar cuvinte drum : " << countChainWords;
	out.close();
}

