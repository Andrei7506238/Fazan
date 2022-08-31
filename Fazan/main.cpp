#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include "Fazan.h"

std::ifstream* loadWords() {
	size_t listArg;
	std::cout << "Lista cuvinte [ 1 - flex | 2 - redus | 3 - custom ] : ";
	std::cin >> listArg;

	char fileName[10] = "";

	switch (listArg) {
	case 1:
		strcpy_s(fileName, "flex.txt");
		break;
	case 2:
		strcpy_s(fileName, "redus.txt");
		break;
	case 3:
		strcpy_s(fileName, "custom.txt");
		break;
	default:
		std::cerr << "[-] Optiune invalida";
		exit(1);
	}

	std::ifstream* inp = new std::ifstream(fileName);
	if (!inp->good()) {
		std::cerr << "[-] EROARE : Fisierul nu a putut fi deschis";
		exit(1);
	}

	return inp;
}

size_t printMenu() {
	size_t option = 0;
	std::cout << "\n====== | FAZAN CHEAT | ====== ";
	std::cout << "\n1. Modul Fazan Cheat (fara duplicate)";
	std::cout << "\n2. Modul Fazan Cheat (cu duplicate)";
	std::cout << "\n3. Modul Extra ";
	std::cout << "\n=============================";

	std::cout << "\n\tIntroduceti alegerea : ";
	std::cin >> option;

	if (option <= 0 || option >= 3) {
		std::cerr << "[-] Optiune invalida";
		exit(1);
	}

	return option;
}

void fazanCheatNoDuplicated(Fazan* x) {
	std::cout << "\n\nA fost activat modul FazanCheat (fara duplicate).";
	std::cout << "\nIntrodu toate cuvintele adversarilor (si cuvantul tau din prima etapa a jocului) cu caracterul '-' in fata pentru a sterge cuvantul din lista de cuvinte acceptate.";
	std::cout << "\nIntrodu cuvantul adversarului aflat inaintea ta fara '-' pentru a sugera un cuvant cu numar cat mai mic de posibilitati de continuare. Cuvantul adversarului si cuvantul sugerat de program sunt sterse automat. ";
	std::cout << "\nIntrodu '0' pentru a opri jocul.\n";

	std::string nw;
	while (true) {
		//Get word input
		std::cout << "\nIntroduceti cuvant : ";
		std::cin >> nw;

		//Check if game is over
		if (nw == "0") break;

		//Check if word marked for deletion, get word without '-'
		bool onlyDelete = (nw[0] == '-');
		if (onlyDelete)	nw = nw.substr(1);

		//Check if word is valid
		if (!x->checkWordExists(nw)) {
			std::cout << "\tCuvant invalid sau deja folosit";
			continue;
		}

		//Delete adversary word
		x->deleteWord(nw);

		//If not marked only for deletion get suggestion
		if (!onlyDelete) {
			auto res = x->suggestWord(nw);

			//If words are avaliable
			if (res.first.length()) {
				std::cout << "\t" << res.first << " [ posibilitati adversar : " << res.second << ((res.second == 0) ? " - FAZAN" : "") << " ]" << std::endl;
				x->deleteWord(res.first);
			}
			//Otherwise round over for advantage player
			else {
				std::cout << "\tFAZAN - nu exista cuvinte disponibile";
			}
		}
	}
}

void fazanCheatDuplicated(Fazan* x) {
	std::cout << "\n\nA fost activat modul FazanCheat (cu duplicate).";
	std::cout << "\nIntrodu cuvantul adversarului aflat inaintea ta pentru a sugera un cuvant cu numar cat mai mic de posibilitati de continuare. Cuvantul adversarului si cuvantul sugerat de program sunt sterse automat. ";
	std::cout << "\nIntrodu '0' pentru a opri jocul.\n";

	std::string nw;
	while (true) {
		//Get word input
		std::cout << "\nIntroduceti cuvant : ";
		std::cin >> nw;

		//Check if game is over
		if (nw == "0") break;

		//Check if word is valid
		if (!x->checkWordExists(nw)) {
			std::cout << "\tCuvant invalid sau deja folosit";
			continue;
		}

		//Get suggestion
		auto res = x->suggestWord(nw);

		//If words are avaliable
		if (res.first.length()) {
			std::cout << "\t" << res.first << " [ posibilitati adversar : " << res.second << ((res.second == 0) ? " - FAZAN" : "") << " ]" << std::endl;
		}
		//Otherwise round over for advantage player
		else {
			std::cout << "\tFAZAN - nu exista cuvinte disponibile";
		}
	}
}

int main() {
	//Get input stream
	std::ifstream* inp = loadWords();

	//Create Fazan Game object and load words
	std::clog << "[+] Incarcare cuvinte ...";
	Fazan* x = new Fazan(*inp);
	std::clog << "\n[+] Au fost incarcate " << x->getNoWords() << " cuvinte.\n";
	inp->close();
	delete inp;

	//Print main menu and get option
	size_t option = printMenu();

	//Menu
	switch (option) {
	case 1:
		fazanCheatNoDuplicated(x);
		break;
	case 2:
		fazanCheatDuplicated(x);
		break;
	case 3:
		std::cout << "Optiune in lucru...";
		break;
	default:
		std::cout << "Alegere incorecta";
	}

}

