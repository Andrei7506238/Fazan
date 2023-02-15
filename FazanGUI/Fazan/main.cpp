#include "FazanDS.h"
#include "FazanCheatGame.h"
#include "Extra.h"
#include <thread>
#include <future>

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
		std::cerr << "[-] EROARE : Fisierul " << fileName <<" nu a putut fi deschis";
		exit(1);
	}

	return inp;
}

size_t printMenu() {
	size_t option = 0;
	std::cout << "\n====== | FAZAN CHEAT | ====== ";
	std::cout << "\n1. Modul Fazan Cheat (fara duplicate)";
	std::cout << "\n2. Modul Fazan Cheat (cu duplicate)";
	std::cout << "\n3. Modul Extra : genereaza fisier cuvinte folosite pentru blocare";
	std::cout << "\n4. Modul Extra : genereaza cel mai lung sir fazan";
	std::cout << "\n=============================";

	std::cout << "\n\tIntroduceti alegerea : ";
	std::cin >> option;

	if (option <= 0 || option > 4) {
		std::cerr << "[-] Optiune invalida";
		exit(1);
	}

	std::cout << std::endl;
	return option;
}


int main() {
	//Get input stream
	std::ifstream* inp = loadWords();

	//Print main menu in separate thread
	std::future<size_t> opt_rez = std::async(&printMenu);

	//Create Fazan Game object and load words
	FazanDataStructure* x = new FazanDataStructure(*inp);
	inp->close();
	delete inp;

	//Get option from printMenu
	size_t option = opt_rez.get();

	//Menu
	switch (option) {
	case 1:
		FazanCheatGame::fazanCheatNoDuplicated(x);
		break;
	case 2:
		FazanCheatGame::fazanCheatDuplicated(x);
		break;
	case 3:
		Extra::generateBlockingWords(x);
		break;
	case 4:
		Extra::generateLongPath(x);
		break;
	}

	delete x;
}

