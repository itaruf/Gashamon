#ifndef __GASHINESCENE_H__
#define __GASHINESCENE_H__

#include "Scene.h"
#include "SpriteManager.hpp"
#include "Gashadex.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <array>
#include <typeinfo>
#include <algorithm>

class GashineScene : public Scene {
private:
	std::shared_ptr<SpriteManager> mySpriteManager;
	std::vector<std::string> myGashamonNames;
public:
	class Monster {
	public:
		NonGashamon nonGashamon;
		Monster() = default;
		~Monster() = default;
	};
	GashamonType gashamonTypes;
	FireSkillList fireSkillList;
	IceSkillList iceSkillList;
	HealingSkillList healingSkillList;
	BuffSkillList buffSkillList;
	DebuffSkillList debuffSkillList;
	NormalSkillList normalSkillList;

	GashineScene(const SpriteManager& spriteManager);
	GashineScene(const GashineScene&) = default;
	GashineScene(GashineScene&&) noexcept = default;
	GashineScene& operator=(const GashineScene&) = delete;
	GashineScene& operator=(GashineScene&&) = default;

	void Render(SDLppRenderer& renderer, SDLppTexture& textTexture, SDL_Rect& textRect) override;

	bool Update(int time) override;

	int GenerateRandomNumber(int min, int max);

	void DrawGashamon(SDLppRenderer& renderer, Gashadex& gashadex);

	void GenerateGashamon(Gashadex& gashadex, int& randomGashamon, std::vector<Skill> skills);

	template<class T>
	inline std::vector<Skill> GenerateAbilities(T& elementalSkills);
	
	int GenerateHP();

	~GashineScene() = default;
};

template<class T>
inline std::vector<Skill> GashineScene::GenerateAbilities(T& elementalSkills) {

	std::vector<Skill> skills;

	// 1 elemental spell
	skills.emplace_back(elementalSkills.skills.at(GenerateRandomNumber(0, static_cast<int>(elementalSkills.skills.size() - 1))));
	//std::cout << "Elemental Spell added: " << skills.at(0).name << std::endl;

	// 1 normal spell
	skills.emplace_back(normalSkillList.skills.at(GenerateRandomNumber(0, static_cast<int>(normalSkillList.skills.size() - 1))));
	//std::cout << "Elemental Spell added: " << skills.at(0).name << std::endl;

	// 1 buff or 1 debuff or 1 healing spell
	int randomSkillElement = GenerateRandomNumber(0, 2);

	switch (randomSkillElement) {
	case 0:
	{
		skills.emplace_back(buffSkillList.skills.at(GenerateRandomNumber(0, static_cast<int>(buffSkillList.skills.size() - 1))));
		//std::cout << "Buff Spell added: " << skills.at(2).name << std::endl;
	}
	break;
	case 1:
	{
		skills.emplace_back(debuffSkillList.skills.at(GenerateRandomNumber(0, static_cast<int>(debuffSkillList.skills.size() - 1))));
		//std::cout << "Buff Spell added: " << skills.at(2).name << std::endl;
	}
	break;
	case 2:
	{
		skills.emplace_back(healingSkillList.skills.at(GenerateRandomNumber(0, static_cast<int>(healingSkillList.skills.size() - 1))));
		//std::cout << "Buff Spell added: " << skills.at(2).name << std::endl;
	}
	break;
	}
	return(skills);
}

#endif // !__GASHINE_H__
