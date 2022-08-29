#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include "Fazan.h"

int main(){
	std::cout << "[+] Incarcare cuvinte ...";
	std::ifstream fin("data.txt");
	Fazan* x = new Fazan(fin);
	fin.close();
	std::cout << "\n[+] Au fost incarcate " << x->getNoWords() << " cuvinte.\n";
	

	std::cout << "\n\nA fost activat modul FazanCheat. Introdu cuvantul adversarului pentru a recomanda un cuvant cu numar cat mai mic de posibilitati de continuare. \n";
	std::string nw;
	while (true) {
		std::cout << "\nIntroduceti cuvant : ";
		std::cin >> nw;

		if (nw == "0") break;
		auto res = x->suggestWord(nw);

		if (res.first.length() == 0)
			std::cout << "\tFAZAN!";
		else
			std::cout << "\t" << res.first << " [ posibilitati adversar : " << res.second << " ]" << std::endl;
	}
}

