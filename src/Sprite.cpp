#include "Sprite.hpp"
#include "SDLppRenderer.hpp"
#include "SDLppTexture.hpp"

Sprite::Sprite(std::shared_ptr<SDLppTexture> texture, const SDL_Rect& rect) :
m_texture(std::move(texture)),
m_rect(rect) //< pas de mouvement du rect car le mouvement et la copie sur des structures ne contenant que des entiers est identique (mais ce n'est pas une erreur)
{
}

const SDL_Rect& Sprite::GetRect() const
{
	return m_rect;
}

const std::shared_ptr<SDLppTexture>& Sprite::GetTexture() const
{
	return m_texture;
}

void Sprite::Draw(SDLppRenderer& renderer, int x, int y)
{
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = m_rect.w;
	destRect.h = m_rect.h;

	Draw(renderer, destRect);
}

void Sprite::Draw(SDLppRenderer& renderer, const SDL_Rect& destRect)
{
	renderer.Copy(*m_texture, m_rect, destRect);
}
