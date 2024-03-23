#pragma once

#include "SDLppTexture.hpp"
#include <SDL.h>
#include <string>

class SDLppWindow;

class SDLppRenderer
{
	friend SDLppWindow;

	public:
		SDLppRenderer(const SDLppRenderer&) = delete;
		SDLppRenderer(SDLppRenderer&& renderer);
		~SDLppRenderer();

		void Clear();

		void Copy(const SDLppTexture& texture);
		void Copy(const SDLppTexture& texture, const SDL_Rect& dstRect);
		void Copy(const SDLppTexture& texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect);

		SDL_Renderer* GetHandle() const;

		void Present();

		void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = SDL_ALPHA_OPAQUE);

		SDLppRenderer& operator=(const SDLppRenderer&) = delete;
		SDLppRenderer& operator=(SDLppRenderer&& renderer);

	private:
		SDLppRenderer(SDL_Renderer* renderer);

		SDL_Renderer* m_renderer;
};