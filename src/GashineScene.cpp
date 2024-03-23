#include "GashineScene.h"

GashineScene::GashineScene(const SpriteManager& spriteManager) : mySpriteManager(std::make_shared<SpriteManager>(spriteManager))
{
	for (unsigned int y = 0; y < 5; ++y)
	{
		for (unsigned int x = 0; x < 4; ++x)
		{
			std::string name = "G_" + std::to_string(x) + "_" + std::to_string(y); // ex: G_1_2
			myGashamonNames.emplace_back(name);
		}
	}
}

void GashineScene::Render(SDLppRenderer& renderer, SDLppTexture& textTexture, SDL_Rect& textRect) {
	renderer.SetDrawColor(65, 105, 225);
	renderer.Clear();
	renderer.Copy(textTexture, textRect);
	renderer.Present();
}

bool GashineScene::Update(int time) {
	const int FPS = 1;
	const int frameDelay = 1000 / FPS;

	auto currentTime = SDL_GetTicks();
	auto elapsedTime = currentTime - time;

	if (elapsedTime < frameDelay) {
		return false;
	}
	return(true);
}

int GashineScene::GenerateRandomNumber(int min, int max) {
	std::random_device r;
	std::default_random_engine e1(r());
	auto uniform_dist = std::uniform_int_distribution<int>(min, max);
	return (uniform_dist(e1));
}

void GashineScene::DrawGashamon(SDLppRenderer& renderer, Gashadex& gashadex) {
	// 1/5 d'obtenir un non-gashamon
	Monster monster;
	std::random_device r;
	std::default_random_engine e1(r());
	int randomNumber = GenerateRandomNumber(1, 5);

	if (randomNumber == 1) {
		std::cout << monster.nonGashamon.name << " drawn ! This won't be added to the Gashadex." << std::endl;
	}
	else {
		int randomGashamon = GenerateRandomNumber(0, static_cast<int>(mySpriteManager.get()->GetMap().size()) - 1);
		std::string nameDrawn = myGashamonNames.at(randomGashamon);

		std::cout << "Gashamon drawn: " << nameDrawn << std::endl;

		/*Print the drawn Gashamon on the screen*/
		mySpriteManager.get()->GetMap().at(myGashamonNames.at(randomGashamon))->Draw(renderer, 500, 250);

		/*Creating the random Gashamon*/

		// Giving random abilities and stats to the drawn gashamon
		int randomSkillElement = GenerateRandomNumber(0, 2);

		switch (randomSkillElement) {
		case 0:
			GenerateGashamon(gashadex, randomGashamon, GenerateAbilities(fireSkillList));
			break;
		case 1:
			GenerateGashamon(gashadex, randomGashamon, GenerateAbilities(iceSkillList));
			break;
		case 2:
			GenerateGashamon(gashadex, randomGashamon, GenerateAbilities(iceSkillList));
			break;
		default:
			break;
		}

		renderer.Present();
	}
	std::cout << std::endl << std::endl;
}

void GashineScene::GenerateGashamon(Gashadex& gashadex, int& randomGashamon, std::vector<Skill> skills) {

	// Choosing a random type 
	int randomType = GenerateRandomNumber(0, static_cast<int>(gashamonTypes.types.size()) - 1);

	std::shared_ptr<Gashamon> gashamon = std::make_shared<Gashamon>(myGashamonNames.at(randomGashamon), mySpriteManager.get()->GetMap().at(myGashamonNames.at(randomGashamon)), GenerateHP(), gashamonTypes.types.at(randomType));

	gashamon.get()->GetSkills() = skills;

	if (gashamon.get()->GetSkills().at(2).GetType() == "Buff") {
		gashamon.get()->GetHasBuffSkill() = true;
	}
	if (gashamon.get()->GetSkills().at(2).GetType() == "Debuff") {
		gashamon.get()->GetHasDebuffSkill() = true;
	}
	if (gashamon.get()->GetSkills().at(2).GetType() == "Heal") {
		gashamon.get()->GetHasHealingSkill() = true;
	}

	gashamon.get()->DisplayStats();
	gashadex.AddGashamon(std::shared_ptr<Gashamon>(gashamon));
}

int GashineScene::GenerateHP() {
	std::random_device r;
	std::default_random_engine e1(r());
	auto uniform_dist = std::uniform_int_distribution<int>(0, 2);
	int randomSkillElement = uniform_dist(e1);

	switch (randomSkillElement) {
	case 0:
		return(200);
		break;
	case 1:
		return (250);
		break;
	case 2:
		return (300);
		break;
	default:
		return {};
		break;
	}
}
