#ifndef __SKILL_H__
#define __SKILL_H__

#include <iostream>
#include <string>

class Skill {
private:
	//std::string type;
	//std::string name;
	//int value;
	//int PP;

	//int initialValue;
	//int initialPP;
public:
	std::string type;
	std::string name;
	int value;
	int PP;

	int initialValue;
	int initialPP;

	Skill(std::string type, std::string name, int value, int PP);

	std::string& GetType();
	std::string& GetName();
	int& GetValue();
	int& GetPP();

	int& GetInitialValue();
	int& GetInitialPP();

	void DiminishPP();

	bool HasPP();

	~Skill() = default;
};

#endif // !__SKILL_H__
