#include "Skill.h"

Skill::Skill(std::string type, std::string name, int value, int PP) : type(std::move(type)), name(std::move(name)), value(value), PP(PP), initialValue(value), initialPP(PP) {}

std::string& Skill::GetType()
{
	return type;
}

std::string& Skill::GetName()
{
	return name;
}

int& Skill::GetValue()
{
	return value;
}

int& Skill::GetPP()
{
	return PP;
}

int& Skill::GetInitialValue()
{
	return initialValue;
}

int& Skill::GetInitialPP()
{
	return initialPP;
}

void Skill::DiminishPP() {
	PP--;
	//std::cout << name << "'s PP diminished. " << name << "'s current PP is: " << PP << std::endl;
}

bool Skill::HasPP() {
	if (PP == 0) {
		return false;
	}
	return true;
}
