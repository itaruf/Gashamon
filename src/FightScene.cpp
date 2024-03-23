#include "FightScene.h"

FightScene::FightScene(const SpriteManager& spriteManager) : pictureManager(std::make_shared<SpriteManager>(spriteManager))
{
}

void FightScene::Render(SDLppRenderer& renderer, SDLppTexture& textTexture, SDL_Rect& textRect) {
	renderer.SetDrawColor(102, 205, 170);
	renderer.Clear();
	renderer.Copy(textTexture, textRect);
	renderer.Present();
}

bool FightScene::Update(int time) {
	const int FPS = 1;
	const int frameDelay = 1000 / FPS;

	auto currentTime = SDL_GetTicks();
	auto elapsedTime = currentTime - time;

	if (elapsedTime < frameDelay) {
		return false;
	}
	return(true);
}

int FightScene::GenerateRandomNumber(int min, int max) {
	std::random_device r;
	std::default_random_engine e1(r());
	auto uniform_dist = std::uniform_int_distribution<int>(min, max);
	return (uniform_dist(e1));
}

void FightScene::StartFight(SDLppRenderer& renderer, Gashadex& gashadex) {
	hasFightStarted = true;
	auto randomFighter = GenerateRandomNumber(0, static_cast<int>(gashadex.GetGashadex().size() - 1));
	auto randomFighter2 = 0;
	do {
		randomFighter2 = GenerateRandomNumber(0, static_cast<int>(gashadex.GetGashadex().size() - 1));
	} while (randomFighter == randomFighter2);

	auto savedTime = SDL_GetTicks();

	while (true) {
		if (gashadex.GetGashadex().at(randomFighter).get()->isDead()) break;
		// Player 1's turn

		savedTime = SDL_GetTicks();
		while (!Update(savedTime)) {}

		renderer.SetDrawColor(144, 238, 144);
		renderer.Clear();
		gashadex.GetGashadex().at(randomFighter)->GetSprite()->Draw(renderer, 150, 150);
		pictureManager.get()->Get("arrow-right").get()->Draw(renderer, 500, 150);
		gashadex.GetGashadex().at(randomFighter2)->GetSprite()->Draw(renderer, 850, 150);
		renderer.Present();

		gashadex.GetGashadex().at(randomFighter)->Use(gashadex.GetGashadex().at(randomFighter2));
		std::cout << std::endl;

		if (gashadex.GetGashadex().at(randomFighter2).get()->isDead()) break;
		// Player 2's turn
		savedTime = SDL_GetTicks();
		while (!Update(savedTime)) {}

		renderer.SetDrawColor(32, 178, 170);
		renderer.Clear();
		renderer.Present();
		gashadex.GetGashadex().at(randomFighter)->GetSprite()->Draw(renderer, 150, 150);
		pictureManager.get()->Get("arrow-left").get()->Draw(renderer, 500, 150);
		gashadex.GetGashadex().at(randomFighter2)->GetSprite()->Draw(renderer, 850, 150);
		renderer.Present();

		gashadex.GetGashadex().at(randomFighter2)->Use(gashadex.GetGashadex().at(randomFighter));
		std::cout << std::endl;

		savedTime = SDL_GetTicks();
		while (!Update(savedTime)) {}

		renderer.Clear();
		gashadex.GetGashadex().at(randomFighter)->GetSprite()->Draw(renderer, 150, 150);
		gashadex.GetGashadex().at(randomFighter2)->GetSprite()->Draw(renderer, 850, 150);
		renderer.Present();

		gashadex.GetGashadex().at(randomFighter)->DisplayStats();
		gashadex.GetGashadex().at(randomFighter2)->DisplayStats();
	}
	DetermineWinner(gashadex, randomFighter, randomFighter2, renderer);
}

bool FightScene::CanStartFight(Gashadex& gashadex) {
	if (gashadex.GetGashadex().size() >= 2) return true;
	std::cout << "Need atleast 2 gashamons to start a fight." << std::endl << std::endl;
	return false;
}

void FightScene::DetermineWinner(Gashadex& gashadex, int& randomFighter, int& randomFighter2, SDLppRenderer& renderer) {
	SDLppFont font("resources/coolvetica.ttf", 60);

	if (gashadex.GetGashadex().at(randomFighter).get()->isDead()) {
		std::cout << gashadex.GetGashadex().at(randomFighter2).get()->GetName() << " won !" << std::endl;
		std::cout << gashadex.GetGashadex().at(randomFighter).get()->GetName() << " lost !" << std::endl;
		std::cout << std::endl;

		SDLppSurface text = font.RenderUTF8Blended("Winner is " + gashadex.GetGashadex().at(randomFighter2).get()->GetName());
		SDLppTexture texture = SDLppTexture::FromSurface(renderer, text);
		SDL_Rect rect = texture.GetRect();
		rect.x = 450;
		rect.y = 500;

		Render(renderer, texture, rect);

		gashadex.GetGashadex().at(randomFighter2).get()->GetSprite()->Draw(renderer, 550, 150);
		gashadex.DeleteGashamon(randomFighter);
	}
	else {
		std::cout << gashadex.GetGashadex().at(randomFighter).get()->GetName() << " won !" << std::endl;
		std::cout << gashadex.GetGashadex().at(randomFighter2).get()->GetName() << " lost !" << std::endl;
		std::cout << std::endl;

		SDLppSurface text = font.RenderUTF8Blended("Winner is " + gashadex.GetGashadex().at(randomFighter).get()->GetName());
		SDLppTexture texture = SDLppTexture::FromSurface(renderer, text);
		SDL_Rect rect = texture.GetRect();
		rect.x = 450;
		rect.y = 500;

		Render(renderer, texture, rect);

		gashadex.GetGashadex().at(randomFighter).get()->GetSprite()->Draw(renderer, 550, 150);
		gashadex.DeleteGashamon(randomFighter2);
	}

	renderer.Present();
	hasFightStarted = false;
}

bool FightScene::GetHasFightStarted() {
	return(hasFightStarted);
}
