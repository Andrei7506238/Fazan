#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include "Fazan.h"

std::ifstream* loadWords(size_t listArg) {
	if (listArg == 0) {
		std::cout << "Lista cuvinte [ 1 - flex | 2 - redus | 3 - custom ] : ";
		std::cin >> listArg;
	}

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
	std::cout << "\n1. Modul Fazan Cheat ";
	std::cout << "\n2. Modul Extra ";
	std::cout << "\n3. Instructiuni ";
	std::cout << "\n============================= ";

	std::cout << "\n\tIntroduceti alegerea : ";
	std::cin >> option;

	if (option <= 0 || option >= 3) {
		std::cerr << "[-] Optiune invalida";
		exit(1);
	}

	return option;
}

void fazanCheat(Fazan* x, size_t rules) {
	//Get rules for word duplication 
	bool allowDuplicated = 0;
	if (!rules) {
		std::cout << "\nRegulament : Se accepta cuvinte duplicate ?";
		std::cout << "\n\tOptiune [ 1-Da, 0-Nu ] : ";
		std::cin >> allowDuplicated;
	}
	else {
		allowDuplicated = rules - 1;
	}

	//Show message
	std::cout << "\n\nA fost activat modul FazanCheat. Introdu cuvantul jucatorului anterior pentru a recomanda un cuvant cu numar cat mai mic de posibilitati de continuare. ";
	if (!allowDuplicated)
		std::cout << "\nIntrodu cuvintele adversarilor cu caracterul '-' in fata pentru a sterge cuvantul din lista de cuvinte acceptate";
	std::cout << "\nIntrodu caracterul '0' pentru a iesi din joc.";
	std::cout << std::endl;
	
	std::string nw;
	while (true) {
		//Get word input
		std::cout << "\nIntroduceti cuvant : ";
		std::cin >> nw;

		//Check if game is over
		if (nw == "0") break;

		//Check if word marked for deletion
		if (!allowDuplicated && nw[0] == '-') {
			if (!x->deleteWord(nw.substr(1)))
				std::cout << "\tCuvant invalid sau deja folosit";
		}
		//If word not marked for deletion
		else {
			//Delete adversary word
			if (nw.length()<3 || !allowDuplicated && !x->deleteWord(nw)) {
				std::cout << "\tCuvant invalid sau deja folosit";
				continue;
			}
			
			//Generate suggestion
			auto res = x->suggestWord(nw);


			//If words are avaliable
			if (res.first.length()) {
				std::cout << "\t" << res.first << " [ posibilitati adversar : " << res.second << " ]" << std::endl;
				if(!allowDuplicated) x->deleteWord(res.first);
			}
			//If round over for advantage player
			else {
				std::cout << "\tFAZAN - nu exista cuvinte disponibile";
			}
		}
	}
}

int main(int argc, char* argv[]) {
	//Read command line argument for list and rules
	size_t listArg = 0;
	size_t rulesArg = 0;

	if (argc>1) {
		if (argc >= 2)
			listArg = atoi(argv[1]);
		if (argc >= 3)
			if (argv[2][0] == 'n') rulesArg = 1;
			if (argv[2][0] == 'y') rulesArg = 2;
			
	}

	//Get input stream
	std::ifstream* inp = loadWords(listArg);

	//Create Fazan Game object and load words
	std::clog << "[+] Incarcare cuvinte ...";
	Fazan* x = new Fazan(*inp);
	std::clog << "\n[+] Au fost incarcate " << x->getNoWords() << " cuvinte.\n";
	inp->close();
	delete inp;

	//Print main menu and get option
	size_t option = printMenu();

	//Menu
	switch (option){
	case 1:
		fazanCheat(x, rulesArg);
	default:
		std::cout << "Not yet build...";
	}
	
}

