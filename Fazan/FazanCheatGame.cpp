#include "FazanCheatGame.h"

void FazanCheatGame::fazanCheatNoDuplicated(FazanDataStructure* x) {
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
void FazanCheatGame::fazanCheatDuplicated(FazanDataStructure* x) {
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