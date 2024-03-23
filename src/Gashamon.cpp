#include "Gashamon.hpp"

Gashamon::Gashamon(std::string name, std::shared_ptr<Sprite> sprite, int health, std::string type) :
	m_sprite(std::move(sprite)),
    name(std::move(name)),
	m_health(health),
	type(std::move(type))
{
}

const std::string& Gashamon::GetName()
{
	return name;
}

const std::string& Gashamon::GetType()
{
	return type;
}

std::vector<Skill>& Gashamon::GetSkills()
{
	return skills;
}

const int& Gashamon::GetInitialHP()
{
	return initialHP;
}

const int& Gashamon::GetLastDamageTaken()
{
	return lastDamageTaken;
}

bool& Gashamon::GetHasDebuffSkill()
{
	return hasDebuffSkill;
}

bool& Gashamon::GetHasBuffSkill()
{
	return hasBuffSkill;
}

bool& Gashamon::GetHasHealingSkill()
{
	return hasHealingSkill;
}

bool& Gashamon::GetIsBuffed()
{
	return isBuffed;
}

bool& Gashamon::GetIsDebuffed()
{
	return isDebuffed;
}

int Gashamon::GetBuffDuration()
{
	return buffDuration;
}

int Gashamon::GetDebuffDuration()
{
	return debuffDuration;
}

void Gashamon::SetLastDamageTaken(const int& value)
{
	lastDamageTaken = value;
}

const std::shared_ptr<Sprite>& Gashamon::GetSprite()
{
	return m_sprite;
}

int& Gashamon::GetHealth() {
	return m_health;
}


bool Gashamon::isDead() {
	if (m_health <= 0) {
		return true;
	}
	return false;
}

int Gashamon::GenerateRandomNumber(int min, int max) {
	std::random_device r;
	std::default_random_engine e1(r());
	auto uniform_dist = std::uniform_int_distribution<int>(min, max);
	return (uniform_dist(e1));
}

void Gashamon::UseFirstSkill(std::shared_ptr<Gashamon> target) {

	if (!skills.at(0).HasPP()) {
		spellCallback = &Gashamon::SpellFailed;
		(this->*spellCallback)(GetName(), skills.at(0).GetName());
		return;
	}

	spellCallback = &Gashamon::SpellUsed;
	(this->*spellCallback)(GetName(), skills.at(0).GetName());
	skills.at(0).DiminishPP();

	target.get()->GetHealth() -= skills.at(0).GetValue();
	target.get()->GetHealth() = std::clamp(target.get()->GetHealth(), 0, target.get()->initialHP);

	std::cout << target.get()->GetName() << " looses " << skills.at(0).GetValue() << " HP ! " << std::endl;

	target->SetLastDamageTaken(skills.at(0).GetValue());
}

void Gashamon::UseSecondSkill(std::shared_ptr<Gashamon> target) {

	spellCallback = &Gashamon::SpellUsed;
	(this->*spellCallback)(GetName(), skills.at(1).GetName());

	target.get()->GetHealth() -= skills.at(1).GetValue();
	target.get()->GetHealth() = std::clamp(target.get()->GetHealth(), 0, target.get()->initialHP);
	target->SetLastDamageTaken(skills.at(1).GetValue());

	std::cout << target.get()->GetName() << " looses " << skills.at(1).GetValue() << " HP ! "  << std::endl;

	target->SetLastDamageTaken(skills.at(1).GetValue());
}

void Gashamon::UseBuffSkill() {
	if (!skills.at(2).HasPP()) {
		spellCallback = &Gashamon::SpellFailed;
		(this->*spellCallback)(GetName(), skills.at(2).GetName());
		return;
	}

	spellCallback = &Gashamon::SpellUsed;
	(this->*spellCallback)(GetName(), skills.at(2).GetName());

	// Si le joueur a déjà été buff
	if (isBuffed) {
		buffDuration = 0;
		skills.at(2).DiminishPP();
		std::cout << GetName() << "'s buff duration extended !" << std::endl;
		return;
	}

	skills.at(2).DiminishPP();

	std::cout << GetName() << " has been buffed !" << std::endl;
	isBuffed = true;

	skills.at(0).GetValue() *= skills.at(2).GetValue();
	skills.at(1).GetValue() *= skills.at(2).GetValue();
	std::cout << skills.at(0).GetName() << " now deals " << skills.at(0).GetValue() << " damages !" << std::endl;
	std::cout << skills.at(1).GetName() << " now deals " << skills.at(1).GetValue() << " damages !" << std::endl;
}

void Gashamon::UseDebuffSkill(std::shared_ptr<Gashamon> target) {
	if (!skills.at(2).HasPP()) {
		spellCallback = &Gashamon::SpellFailed;
		(this->*spellCallback)(GetName(), skills.at(2).GetName());
		return;
	}
	spellCallback = &Gashamon::SpellUsed;
	(this->*spellCallback)(GetName(), skills.at(2).GetName());

	// Si l'ennemi a déjà été debuff
	if (target.get()->isDebuffed) {
		target.get()->debuffDuration = 0;
		skills.at(2).DiminishPP();
		std::cout << target.get()->GetName() << "'s debuff duration extended !" << std::endl;
		return;
	}

	skills.at(2).DiminishPP();

	std::cout << target.get()->GetName() << " has been debuffed !" << std::endl;
	target.get()->isBuffed = false;
	target.get()->isDebuffed = true;

	target.get()->skills.at(0).GetValue() /= skills.at(2).GetValue();
	target.get()->skills.at(1).GetValue() /= skills.at(2).GetValue();
	std::cout << target.get()->skills.at(0).GetName() << " now deals " << target.get()->skills.at(0).GetValue() << " damages !" << std::endl;
	std::cout << target.get()->skills.at(1).GetName() << " now deals " << target.get()->skills.at(1).GetValue() << " damages !" << std::endl;
}

void Gashamon::RevertSkillValueBack() {
	std::cout << GetName() << "'s skills values reverted back to normal ! " << std::endl;
	skills.at(0).value = skills.at(0).initialValue;
	skills.at(1).value = skills.at(1).initialValue;
}

void Gashamon::DisplayStats()
{
	int max = 80;
	std::string title = "Stats Summary";
	std::cout << std::setw((max + title.length()) / 2) << title << std::endl;
	std::cout << std::setw((max + GetName().length()) / 2) << GetName() << std::endl;
	std::cout << std::setw(max) << std::setfill('-') << " " << std::setfill(' ') << std::endl;
	std::cout << "HP: " << GetHealth() << "/" << GetInitialHP() << std::endl;
	std::cout << "Skill n-1: " << std::setw((max / 4)) << std::left << GetSkills().at(0).GetName() << std::right << "Value: " << GetSkills().at(0).GetValue() << "/" << GetSkills().at(0).GetInitialValue() << std::setw((max / 4)) << std::right << std::setw((max / 4)) << "PP: " << GetSkills().at(0).GetPP() << "/" << GetSkills().at(0).GetInitialPP()  << std::endl;
	std::cout << "Skill n-2: " << std::setw((max / 4)) << std::left << GetSkills().at(1).GetName() << std::right << "Value: " << GetSkills().at(1).GetValue() << "/" << GetSkills().at(1).GetInitialValue() << std::setw((max / 4)) << std::right << std::setw((max / 4)) << "PP: " << GetSkills().at(1).GetPP() << "/" << GetSkills().at(1).GetInitialPP() << std::endl;
	std::cout << "Skill n-3: " << std::setw((max / 4)) << std::left << GetSkills().at(2).GetName() << std::left << "Value: " << GetSkills().at(2).GetValue() << "/" << GetSkills().at(2).GetInitialValue() << std::setw((max / 4)) << std::right << std::setw((max / 4)) << "PP: " << GetSkills().at(2).GetPP() << "/" << GetSkills().at(2).GetInitialPP() << std::endl;
	std::cout << std::setw(max) << std::setfill('-') << " " << std::setfill(' ') << std::endl;
	std::cout << std::endl;
}

void Gashamon::SpellUsed(const std::string& name, std::string& spell) 
{
	std::cout << name << " uses " << spell << " !" << std::endl;
}

void Gashamon::SpellFailed(const std::string& name, std::string& spell)
{
	std::cout << name << " tries to use " << spell << " but there's no PP left !" << std::endl;
}

void Gashamon::Use(std::shared_ptr<Gashamon> target) {

	const int FPS = 50;
	const int frameDelay = 5000 / FPS;
	auto savedTime = SDL_GetTicks();

	while (true) {
		auto currentTime = SDL_GetTicks();
		auto elapsedTime = currentTime - savedTime;

		if (elapsedTime < frameDelay) {
			continue;
		}
		savedTime = currentTime;

		std::cout << "It's " << GetName() << "'s turn !" << std::endl;

		#pragma region Revert Skill Values 
		if (buffDuration > 2) {
			buffDuration = 0;
			isBuffed = false;
			RevertSkillValueBack();
		}

		if (debuffDuration > 2) {
			debuffDuration = 0;
			isDebuffed = false;
			RevertSkillValueBack();
		}
		#pragma endregion Revert Skill Values 

		if (isBuffed) buffDuration++;
		if (isDebuffed) debuffDuration++;

		bool canUseFirstSkill = true;
		bool canUseThirdSkill = true;

		//std::cout << "Last Damage Taken: " << GetLastDamageTaken() << std::endl;

		/*Si le joueur a été buff ou debuff : ramener les stats à la normale après X tours*/
       
		/*On décide de rentre certaines actions "certaines" (ex: finir l'ennemi, se soigner, ...)*/
        #pragma region Certain Events
		// Checker si le joueur a des PP => sinon on utilise une attaque normale
        #pragma region HasPP
		if (!skills.at(0).HasPP()) {
			canUseFirstSkill = false;
		}

		if (!skills.at(2).HasPP()) {
			canUseThirdSkill = false;
		}
        #pragma endregion HasPP

		// Utiliser une attaque à PP illimitée
		if (!canUseFirstSkill && !canUseThirdSkill) {
			UseSecondSkill(target);
			break; // On arrête l'action du joueur
		}

		// Achever l'ennemi dès que possible 
        #pragma region Finish enemy
		// Lancer en priorité un sort élémentaire de dégâts si l'ennemi est sur le point de mourir
		if (target.get()->GetHealth() <= skills.at(0).GetValue() && canUseFirstSkill) {
			//std::cout << "Can finish the target !" << std::endl;
			UseFirstSkill(target);
			break; // On arrête l'action du joueur
		}

		// Lancer en priorité un sort basic de dégâts si l'ennemi est sur le point de mourir
		if (target.get()->GetHealth() <= skills.at(1).GetValue()) {
			//std::cout << "Can finish the target !" << std::endl;
			UseSecondSkill(target);
			break; // On arrête l'action du joueur
		}
        #pragma endregion Finish enemy

		// Lancer en priorité un sort de soin si impossibilité d'achever l'ennemi
        #pragma region Heal Yourself !
		if (hasHealingSkill && skills.at(2).HasPP()) {
			if (m_health <= GetLastDamageTaken()) {
				std::cout << GetName() << " uses " << skills.at(2).GetName() << " !" << std::endl;
				std::cout << GetName() << " heals itself for " << skills.at(2).GetValue() << " HP !" << std::endl;
				skills.at(2).DiminishPP();

				m_health += skills.at(2).GetValue();
				m_health = std::clamp(m_health, 0, initialHP);

				break;  // On arrête l'action du joueur
			}
		}
        #pragma endregion Heal Yourself !

        #pragma endregion Certain Events

        #pragma region Random Events 
		int random = GenerateRandomNumber(0, 2);

		switch (random)
		{
		case 0:
			UseFirstSkill(target);
			break;
		case 1:
			UseSecondSkill(target);
			break;
		case 2:
			if (hasBuffSkill) {
				UseBuffSkill();
				break;
			}
			if (hasDebuffSkill) {
				UseDebuffSkill(target);
				break;
			}
			else {
				random = GenerateRandomNumber(0, 1);
				switch (random) {
				case 0:
					UseFirstSkill(target);
					break;
				case 1:
					UseSecondSkill(target);
					break;
				}
			}
			break;
		default:
			break;
		}
		break;

        #pragma endregion Random Events 
	}
}
