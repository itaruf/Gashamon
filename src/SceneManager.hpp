#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "FightScene.h"
#include "GashadexScene.h"
#include "ProjetS1Scene.h"
#include "GashineScene.h"
#include "Gashadex.h"

#include "SDLpp.hpp"
#include "SDLppTexture.hpp"
#include "SDLppWindow.hpp"
#include "SDLppFont.hpp"
#include "SDLppTTF.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class SceneManager : public Scene {
private:
	FightScene fightScene;
	GashadexScene gashadexScene;
	ProjetS1Scene projetS1Scene;
	GashineScene gashineScene;
public:
	SceneManager(FightScene& fightScene, GashadexScene& gashadexScene, ProjetS1Scene& projetS1Scene, GashineScene& gashineScene);
	
	void Render(SDLppRenderer& renderer, SDLppTexture& textTexture, SDL_Rect& textRect) override;

	bool Update(int time) override;

	void SetProjetS1Scene(SDLppFont& font, SDLppRenderer& renderer);

	void SetGashadexScene(SDLppFont& font, SDLppRenderer& renderer);

	void SetGashineScene(SDLppFont& font, SDLppRenderer& renderer);

	void SetGashineLockedScene(SDLppFont& font, SDLppRenderer& renderer);

	void SetFightingScene(SDLppFont& font, SDLppRenderer& renderer);

	void SwapScene(SDLpp& sdl, Gashadex& gashadex, SDLppFont& font, SDLppRenderer& renderer);

	FightScene& GetFightScene();
	GashadexScene& GetGashadexScene();
	ProjetS1Scene& GetProjetS1Scene();
	GashineScene& GetGashineScene();

	~SceneManager() = default;
};
#endif // !__SCENEMANAGER_H__
