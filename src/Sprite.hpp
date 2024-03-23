#pragma once

#include <memory> //< std::shared_ptr
#include <SDL.h>

// Les déclarations anticipées permettent d'utiliser les types sous forme de pointeur/référence sans devoir inclure les headers
class SDLppRenderer;
class SDLppTexture;

class Sprite
{
	public:
		Sprite(std::shared_ptr<SDLppTexture> texture, const SDL_Rect& rect);
		Sprite(const Sprite&) = default;
		Sprite(Sprite&&) noexcept = default;
		~Sprite() = default;

		void Draw(SDLppRenderer& renderer, int x, int y);
		void Draw(SDLppRenderer& renderer, const SDL_Rect& destRect);

		const SDL_Rect& GetRect() const;
		const std::shared_ptr<SDLppTexture>& GetTexture() const;

		Sprite& operator=(const Sprite& sprite) = default;
		Sprite& operator=(Sprite&& sprite) noexcept = default;

	private:
		std::shared_ptr<SDLppTexture> m_texture;
		SDL_Rect m_rect;
};
