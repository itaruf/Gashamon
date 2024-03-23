#ifndef __ProjetS1Scene_H__
#define __ProjetS1Scene_H__

#include "Scene.h"
#include "Gashadex.h"
#include "SpriteManager.hpp"

#include "SDLpp.hpp"
#include "SDLppTexture.hpp"
#include "SDLppWindow.hpp"
#include "SDLppFont.hpp"
#include "SDLppTTF.hpp"

class ProjetS1Scene : public Scene {
private:
	std::shared_ptr<SpriteManager> mySpriteManager;
public:
	ProjetS1Scene(const SpriteManager& spriteManager);

	void Render(SDLppRenderer& renderer, SDLppTexture& textTexture, SDL_Rect& textRect) override;

	bool Update(int time) override;
};

#endif // !__ProjetS1Scene_H__
