#include "Extra.h"

void Extra::generateBlockingWords(FazanDataStructure* x){
	size_t countBlockingWords = 0;
	std::ofstream out("blockingWords.txt");
	if (!out.good()) {
		std::cerr << "[-] EROARE : Fisierul \"blockingWords.txt\" nu a putut fi deschis pentru scriere";
		exit(1);
	}

	for (size_t line = 0; line < 961; line++) {
		out << "\n " << MorphoAnalyzer::groupInvConverter(line) << "\t";
		auto lst = x->getBlockingWords(line);
		countBlockingWords += lst.size();

		for (auto& blockingWord : lst)
			out << blockingWord << " ";
	}

	std::cout << "Fisier \"blockingWords.txt\" generat. Numar cuvinte fazan : " << countBlockingWords;
	out.close();
}

void Extra::generateLongestFazan(FazanDataStructure* x){
}

