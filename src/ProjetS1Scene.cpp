#include "ProjetS1Scene.h"

ProjetS1Scene::ProjetS1Scene(const SpriteManager& spriteManager) : mySpriteManager(std::make_shared<SpriteManager>(spriteManager)) {}

void ProjetS1Scene::Render(SDLppRenderer& renderer, SDLppTexture& textTexture, SDL_Rect& textRect) {
	renderer.SetDrawColor(147, 112, 219);
	renderer.Clear(); // On supprime l'affichage précédent
	renderer.Copy(textTexture, textRect);

	std::shared_ptr<SDLppTexture> gashamonTexture = std::make_shared<SDLppTexture>(SDLppTexture::FromFile(renderer, "resources/gashamons.png"));
	SDL_Rect rect = gashamonTexture->GetRect();
	const unsigned int gashamonX = 4; //< Nombre de Gashasmons en X
	const unsigned int gashamonY = 5; //< Nombre de Gashasmons en Y

	rect.x = 0;
	rect.y = 0;
	rect.w /= gashamonX;
	rect.h /= gashamonY;

	for (unsigned int y = 0; y < gashamonY; ++y)
	{
		for (unsigned int x = 0; x < gashamonX; ++x)
		{
			std::string name = "G_" + std::to_string(x) + "_" + std::to_string(y); // ex: G_1_2
			(mySpriteManager.get()->Get(name))->Draw(renderer, rect.x, rect.y);

			rect.x += rect.w;
		}
		rect.x = 0;
		rect.y += rect.h;
	}
	renderer.Present();
}

bool ProjetS1Scene::Update(int time) {
	const int FPS = 1;
	const int frameDelay = 1000 / FPS;

	auto currentTime = SDL_GetTicks();
	auto elapsedTime = currentTime - time;

	if (elapsedTime < frameDelay) {
		return false;
	}
	return(true);
}