#ifndef __SCENE_H__
#define __SCENE_H__

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <stdlib.h>
#include <memory>

#include "SDLpp.hpp"
#include "SDLppTexture.hpp"
#include "SDLppWindow.hpp"
#include "SDLppFont.hpp"
#include "SDLppTTF.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Scene {
public:
	virtual void Render(SDLppRenderer& renderer, SDLppTexture& textTexture, SDL_Rect& textRect) = 0; 
	virtual bool Update(int time) = 0;
	virtual ~Scene() = default;
};

#endif // !__SCENE_H__


