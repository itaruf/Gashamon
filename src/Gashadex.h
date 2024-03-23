#ifndef __GASHADEX_H__
#define __GASHADEX_H__

#include "Gashamon.hpp"

#include <numeric>
#include <stdlib.h>

class Gashadex {
private:
	static constexpr const int myGashadexCapacity = 10;
	std::vector<std::shared_ptr<Gashamon>> myGashadex;
public:
	Gashadex() = default;
	Gashadex(const Gashadex&) = default;
	Gashadex(Gashadex&&) noexcept = default;
	Gashadex& operator=(const Gashadex&) = delete;
	Gashadex& operator=(Gashadex&&) = default;
	~Gashadex() = default;

	bool IsGashadexFull();

	bool AddGashamon(std::shared_ptr<Gashamon> gashamon);

	// Autoriser plusieurs ajouts d'un coup mais ne pas enregistrer le surplus dans le gashadex ?
	bool AddGashamon(std::vector<std::shared_ptr<Gashamon>> myGashamonVector);

	void DisplayGashadex();

	bool IsGashadexEmpty();

	void DeleteGashamon(int& randomFighter);

	std::vector<std::shared_ptr<Gashamon>>& GetGashadex();
};

#endif // !__GASHADEX_H__


