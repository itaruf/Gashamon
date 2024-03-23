#ifndef __FIGHTSCENE_H__
#define __FIGHTSCENE_H__

#include "Scene.h"
#include "Gashadex.h"
#include "SpriteManager.hpp"

#include "SDLpp.hpp"
#include "SDLppTexture.hpp"
#include "SDLppWindow.hpp"
#include "SDLppFont.hpp"
#include "SDLppTTF.hpp"

#include <iostream>

class FightScene : public Scene {
private :	
	bool hasFightStarted = false;
	std::shared_ptr<SpriteManager> pictureManager;
public:
	FightScene(const SpriteManager& spriteManager);

	void Render(SDLppRenderer& renderer, SDLppTexture& textTexture, SDL_Rect& textRect) override;

	bool Update(int time) override;

	int GenerateRandomNumber(int min, int max);

	void StartFight(SDLppRenderer& renderer, Gashadex& gashadex);

	bool CanStartFight(Gashadex& gashadex);

	void DetermineWinner(Gashadex& gashadex, int& randomFighter, int& randomFighter2, SDLppRenderer& renderer);

	bool GetHasFightStarted();

	~FightScene() = default;
};

#endif // !__FIGHTSCENE_H__
