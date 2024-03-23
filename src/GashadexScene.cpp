#include "GashadexScene.h"

GashadexScene::GashadexScene(const Gashadex& gashadex) : myGashadex(std::make_shared<Gashadex>(gashadex)) {}

void GashadexScene::Render(SDLppRenderer& renderer, SDLppTexture& textTexture, SDL_Rect& textRect) {
	int x = 150, y = 0;
	int spaceBetween = 250;
	int cut = 1000;
	renderer.SetDrawColor(240, 128, 128);
	renderer.Clear();
	renderer.Copy(textTexture, textRect);

	for (auto it = myGashadex.get()->GetGashadex().begin(); it != myGashadex.get()->GetGashadex().end(); it++) {
		((*it)->GetSprite())->Draw(renderer, x, y);
		x += spaceBetween;

		if (x > cut) {
			y += 150;
			x = 150;
		}
	}
	renderer.Present();
}

void GashadexScene::FillGashadex(Gashadex& gashadex) {
	if (gashadex.GetGashadex().size() != myGashadex.get()->GetGashadex().size()) {
		size_t difference = gashadex.GetGashadex().size() - myGashadex.get()->GetGashadex().size();
		int gashadexSize = static_cast<int>(myGashadex.get()->GetGashadex().size());
		for (size_t i = 0; i < difference; i++) {
			(myGashadex.get()->GetGashadex()).emplace_back(gashadex.GetGashadex().at(gashadexSize + i));
		}
	}
}

void GashadexScene::UpdateGashadex(Gashadex& gashadex) {
	myGashadex.get()->GetGashadex() = gashadex.GetGashadex();
}

bool GashadexScene::Update(int time) {
	const int FPS = 1;
	const int frameDelay = 1000 / FPS;

	auto currentTime = SDL_GetTicks();
	auto elapsedTime = currentTime - time;

	if (elapsedTime < frameDelay) {
		return false;
	}
	return(true);
}