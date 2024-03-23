#include "SceneManager.hpp"

SceneManager::SceneManager(FightScene& fightScene, GashadexScene& gashadexScene, ProjetS1Scene& projetS1Scene, GashineScene& gashineScene) :fightScene(fightScene), gashadexScene(gashadexScene), projetS1Scene(projetS1Scene), gashineScene(gashineScene) {}

void SceneManager::Render(SDLppRenderer& renderer, SDLppTexture& textTexture, SDL_Rect& textRect)
{
}

bool SceneManager::Update(int time) {
	const int FPS = 30;
	const int frameDelay = 1000 / FPS;

	auto currentTime = SDL_GetTicks();
	auto elapsedTime = currentTime - time;

	if (elapsedTime < frameDelay) {
		return false;
	}
	return (true);
}

void SceneManager::SetProjetS1Scene(SDLppFont& font, SDLppRenderer& renderer) {
	SDLppSurface text = font.RenderUTF8Blended("Projet S1 !");
	SDLppTexture texture = SDLppTexture::FromSurface(renderer, text);
	SDL_Rect rect = texture.GetRect();
	rect.x = 1000;
	rect.y = 500;

	projetS1Scene.Render(renderer, texture, rect);
}

void SceneManager::SetGashadexScene(SDLppFont& font, SDLppRenderer& renderer) {
	SDLppSurface text = font.RenderUTF8Blended("Gashadex !");
	SDLppTexture texture = SDLppTexture::FromSurface(renderer, text);
	SDL_Rect rect = texture.GetRect();
	rect.x = 100;
	rect.y = 500;

	gashadexScene.Render(renderer, texture, rect);
}

void SceneManager::SetGashineScene(SDLppFont& font, SDLppRenderer& renderer) {
	SDLppSurface text = font.RenderUTF8Blended("Gashine !");
	SDLppTexture texture = SDLppTexture::FromSurface(renderer, text);
	SDL_Rect rect = texture.GetRect();
	rect.x = 525;
	rect.y = 100;

	gashineScene.Render(renderer, texture, rect);
}

void SceneManager::SetGashineLockedScene(SDLppFont& font, SDLppRenderer& renderer) {
	SDLppSurface text = font.RenderUTF8Blended("The Gashine is temporarily locked !");
	SDLppTexture texture = SDLppTexture::FromSurface(renderer, text);
	SDL_Rect rect = texture.GetRect();
	rect.x = 250;
	rect.y = 350;

	gashineScene.Render(renderer, texture, rect);
}

void SceneManager::SetFightingScene(SDLppFont& font, SDLppRenderer& renderer) {
	SDLppSurface text = font.RenderUTF8Blended("Fight !");
	SDLppTexture texture = SDLppTexture::FromSurface(renderer, text);
	SDL_Rect rect = texture.GetRect();
	rect.x = 550;
	rect.y = 600;

	fightScene.Render(renderer, texture, rect);
}

void SceneManager::SwapScene(SDLpp& sdl, Gashadex& gashadex, SDLppFont& font, SDLppRenderer& renderer) {
	auto savedTime = SDL_GetTicks();
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	bool running = true;
	while (running)
	{
		SDL_Event event;
		while (sdl.PollEvent(event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				if (!Update(savedTime)) {
					continue;
				}
				savedTime = SDL_GetTicks();
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
					SetGashadexScene(font, renderer);
					gashadex.DisplayGashadex();
					break;
				case SDLK_RIGHT:
					SetProjetS1Scene(font, renderer);
					break;
				case SDLK_UP:
					if (!gashadex.IsGashadexFull()) {
						SetGashineScene(font, renderer);
						gashineScene.DrawGashamon(renderer, gashadex);
						gashadexScene.FillGashadex(gashadex);
					}
					else
						SetGashineLockedScene(font, renderer);
					break;
				case SDLK_DOWN:
					if (!gashadex.IsGashadexEmpty() && fightScene.CanStartFight(gashadex)) {
						if (!fightScene.GetHasFightStarted()) {
							SetFightingScene(font, renderer);
							fightScene.StartFight(renderer, gashadex);
							break;
						}
					}
					break;
				case SDLK_ESCAPE:
					running = false;
					break;
				default:
					break;
				}
			default:
				gashadexScene.UpdateGashadex(gashadex);
				break;
			}
		}
	}
}

FightScene& SceneManager::GetFightScene() {
	return(fightScene);
}

GashadexScene& SceneManager::GetGashadexScene() {
	return(gashadexScene);
}

ProjetS1Scene& SceneManager::GetProjetS1Scene() {
	return(projetS1Scene);
}

GashineScene& SceneManager::GetGashineScene() {
	return(gashineScene);
}
