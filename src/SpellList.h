#pragma once

#include <memory>
#include <string> 
#include <vector>
#include <tuple>
#include <iostream>
#include <random>
#include <cmath>

struct ElectricSkills {
	std::vector<std::tuple<std::string, int, int, std::string>> skills =
	{
		std::make_tuple("Zio", 25, 10, "ELEC"), std::make_tuple("Zionga", 50, 10, "ELEK")
	};
};

struct FireSkills {
	std::vector<std::tuple<std::string, int, int, std::string>> skills =
	{
		std::make_tuple("Agi", 25, 10, "FIRE"), std::make_tuple("Agilao", 50, 10, "FIRE")
	};
};

struct IceSkills {
	std::vector<std::tuple<std::string, int, int, std::string>> skills =
	{
		std::make_tuple("Bufu", 25, 10, "ICE"), std::make_tuple("Bufula", 50, 10, "ICE")
	};
};

struct WindSkills {
	std::vector<std::tuple<std::string, int, int, std::string>> skills =
	{
		std::make_tuple("Garu", 25, 10, "WIND"), std::make_tuple("Garula", 50, 10, "WIND")
	};
};

struct BasicSkills {
	std::vector<std::tuple<std::string, int, int, std::string>> skills =
	{
		std::make_tuple("Tackle", 15, 0, "NORMAL"), std::make_tuple("Quick Attack", 20, 0, "NORMAL")
	};
};

struct BuffSkills {
	std::vector<std::tuple<std::string, int, int, std::string>> skills =
	{
		std::make_tuple("Tarukaja", 2, 2, "BUFF")
	};
};

struct DeBuffSkills {
	std::vector<std::tuple<std::string, int, int, std::string>> skills =
	{
		std::make_tuple("Tarunda", 2, 2, "DEBUFF")
	};
};

struct HealingSkills {
	std::vector<std::tuple<std::string, int, int, std::string>> skills =
	{
		std::make_tuple("Dia", 50, 2, "HEAL") , std::make_tuple("Diarama", 100, 1, "HEAL")
	};
};