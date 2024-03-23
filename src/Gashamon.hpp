#ifndef __GASHAMON_H__
#define __GASHAMON_H__

#include "Sprite.hpp"
#include "SpellList.h"
#include "Skill.h"

#include <iomanip>
#include <memory>
#include <string> 
#include <vector>
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>

class Gashamon
{
private:
	int m_health;
	std::shared_ptr<Sprite> m_sprite;
	std::string name;
	std::string type;
	std::vector<Skill> skills;

	const int initialHP = m_health;
	int lastDamageTaken = 0;

	bool hasDebuffSkill = false;
	bool hasBuffSkill = false;
	bool hasHealingSkill = false;
	bool isBuffed = false;
	bool isDebuffed = false;

	inline static int buffDuration = 0;
	inline static int debuffDuration = 0;

public:
	Gashamon(std::string name, std::shared_ptr<Sprite> sprite, int health, std::string type);
	Gashamon(const Gashamon&) = delete;
	Gashamon(Gashamon&&) noexcept = default;
	Gashamon& operator=(const Gashamon&) = delete;
	Gashamon& operator=(Gashamon&&) noexcept = default;
	~Gashamon() = default;

	int& GetHealth();
	const std::shared_ptr<Sprite>& GetSprite();
	const std::string& GetName();
	const std::string& GetType();
	std::vector<Skill>& GetSkills();

	const int& GetInitialHP();
	const int& GetLastDamageTaken();

	bool& GetHasDebuffSkill();
	bool& GetHasBuffSkill();
	bool& GetHasHealingSkill();
	bool& GetIsBuffed();
	bool& GetIsDebuffed();

	static int GetBuffDuration();	
	static int GetDebuffDuration();

	void (Gashamon::* spellCallback)(const std::string&, std::string&) = nullptr; // test function pointer

	void SetLastDamageTaken(const int& value);

	bool isDead();

	int GenerateRandomNumber(int min, int max);

	void UseFirstSkill(std::shared_ptr<Gashamon> target);

	void UseSecondSkill(std::shared_ptr<Gashamon> target);

	void UseBuffSkill();

	void UseDebuffSkill(std::shared_ptr<Gashamon> target);

	void RevertSkillValueBack();

	void DisplayStats();

	void SpellUsed(const std::string& name, std::string& spell);

	void SpellFailed(const std::string& name, std::string& spell);

	void Use(std::shared_ptr<Gashamon> target);
};

struct NonGashamon {
	std::string name = "Non Gashamon";
};

struct GashamonType {
	std::vector<std::string> types = {
		{"Fire"}, {"Ice" }
	};
};

struct FireSkillList {
	std::vector<Skill> skills = {
		{"Fire", "Agi", 25, 10},
		{"Fire", "Agilao", 50, 5}
	};
};

struct IceSkillList {
	std::vector<Skill> skills = {
		{"Ice", "Bufu", 25, 10},
		{"Ice", "Bufula", 50, 5}
	};
};

struct HealingSkillList {
	std::vector<Skill> skills = {
		{"Heal", "Dia", 50, 2},
		{"Heal", "Diarama", 100, 1}
	};
};

struct BuffSkillList {
	std::vector<Skill> skills = {
		{"Buff", "Tarukaja", 2, 2},
	};
};

struct DebuffSkillList {
	std::vector<Skill> skills = {
		{"Debuff", "Tarunda", 2, 2},
	};
};

struct NormalSkillList {
	std::vector<Skill> skills = {
		{"Normal","Tackle", 15, -1},
		{"Normal","Quick Attack", 20, -1},
	};
};

#endif // !__GASHAMON_H__