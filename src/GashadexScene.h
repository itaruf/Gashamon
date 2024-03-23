#ifndef __GASHADEXSCENE_H__
#define __GASHADEXSCENE_H__

#include "Scene.h"
#include "Gashadex.h"

#include "SDLpp.hpp"
#include "SDLppTexture.hpp"
#include "SDLppWindow.hpp"
#include "SDLppFont.hpp"
#include "SDLppTTF.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class GashadexScene : public Scene {
private : 
	std::shared_ptr<Gashadex> myGashadex;
public:
	GashadexScene(const Gashadex& gashadex);

	void Render(SDLppRenderer& renderer, SDLppTexture& textTexture, SDL_Rect& textRect) override;

	void FillGashadex(Gashadex& gashadex);

	void UpdateGashadex(Gashadex& gashadex);

	bool Update(int time) override;
};

#endif // !__GASHADEXSCENE_H__
