#include "Gashadex.h"

bool Gashadex::IsGashadexFull() {
	if (myGashadex.size() == myGashadexCapacity) {
		std::cout << "The Gashadex is full ! The Gashine is temporarily locked." << std::endl << std::endl;
		return true;
	}
	return false;
}

bool Gashadex::AddGashamon(std::shared_ptr<Gashamon> gashamon) {
	if (IsGashadexFull()) return false;
	myGashadex.emplace_back(gashamon);
	return true;
}

// Autoriser plusieurs ajouts d'un coup mais ne pas enregistrer le surplus dans le gashadex ?

bool Gashadex::AddGashamon(std::vector<std::shared_ptr<Gashamon>> myGashamonVector) {
	if (IsGashadexFull()) return false;
	for (auto it = myGashamonVector.begin(); it != myGashamonVector.end(); it++) {
		if (!IsGashadexFull()) {
			myGashadex.emplace_back(*it);
			continue;
		}
		break;
	}
	return true;
}

void Gashadex::DisplayGashadex() {
	if (IsGashadexEmpty()) return;
	int max = 80;
	std::string title = "GASHADEX :";
	std::cout << std::setw((max + title.length()) / 2) << title << std::endl << std::endl;
	std::for_each(myGashadex.begin(), myGashadex.end(), [](std::shared_ptr<Gashamon> gashamon) {
		gashamon->DisplayStats();
		});
	std::cout << std::endl;
}

bool Gashadex::IsGashadexEmpty() {
	if (myGashadex.size() == 0) {
		std::cout << "The Gashadex is empty" << std::endl << std::endl;
		return true;
	}
	return false;
}

void Gashadex::DeleteGashamon(int& randomFighter) {
	myGashadex.erase(myGashadex.begin() + randomFighter);
}

std::vector<std::shared_ptr<Gashamon>>& Gashadex::GetGashadex() {
	return(myGashadex);
}
