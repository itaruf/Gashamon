#include "Scene.h"
#include "Gashamon.hpp"
#include "Skill.h"
#include "SpellList.h"
#include "Sprite.hpp"

#include "Gashadex.h"
#include "ProjetS1Scene.h"
#include "FightScene.h"
#include "GashineScene.h"
#include "GashadexScene.h"
#include "SceneManager.hpp"
#include "SpriteManager.hpp"

#include "SDLpp.hpp"
#include "SDLppTexture.hpp"
#include "SDLppWindow.hpp"
#include "SDLppFont.hpp"
#include "SDLppTTF.hpp"

#include <cstdlib>
#include <iostream>
#include <stdlib.h>

#ifdef _WIN32	
#define WINPAUSE system("pause")
#endif

void RegisterGashamons(SDLppRenderer& renderer, SpriteManager& spriteManager);
void RenderFirstScreen(SDLppFont& font, SDLppRenderer& renderer);
void RegisterPictures(SDLppRenderer& renderer, SpriteManager& spriteManager, std::shared_ptr<SDLppTexture>& texture, std::string name);

int main(int argc, char* argv[])
{
	/*try
	{*/
		/*SDLpp sdl;
		SDLppTTF ttfInit;
		SDLppFont fontFirstScreen("resources/coolvetica.ttf", 25);
		SDLppFont font("resources/coolvetica.ttf", 48);*/
		SDLppWindow window("Ma super fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720);
		SDLppRenderer renderer = window.CreateRenderer(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		
		/*RenderFirstScreen(fontFirstScreen, renderer);

		SpriteManager spriteManager;
		RegisterGashamons(renderer, spriteManager);

		SpriteManager picturesManager;
		std::shared_ptr<SDLppTexture> arrowRightTexture = std::make_shared<SDLppTexture>(SDLppTexture::FromFile(renderer, "resources/arrow-right.png"));
		RegisterPictures(renderer, picturesManager, arrowRightTexture, "arrow-right");
		std::shared_ptr<SDLppTexture> arrowLeftTexture = std::make_shared<SDLppTexture>(SDLppTexture::FromFile(renderer, "resources/arrow-left.png"));
		RegisterPictures(renderer, picturesManager, arrowLeftTexture, "arrow-left");

		Gashadex gashadex;
		ProjetS1Scene projetS1Scene(spriteManager);
		GashadexScene gashadexScene(gashadex);
		GashineScene gashineScene(spriteManager);
		FightScene fightScene(picturesManager);

		SceneManager sceneManager(fightScene, gashadexScene, projetS1Scene, gashineScene);
		sceneManager.SwapScene(sdl, gashadex, font, renderer);*/

		//WINPAUSE;
		/*return 0;*/
	/*}*/
	/*catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}*/
		SDL_Delay(2000);
}

void RegisterPictures(SDLppRenderer& renderer, SpriteManager& spriteManager, std::shared_ptr<SDLppTexture>& texture, std::string name) {
	SDL_Rect rect = texture->GetRect();
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(texture, rect);
	spriteManager.Register(std::move(name), std::move(sprite));
}


void RegisterGashamons(SDLppRenderer& renderer, SpriteManager& spriteManager)
{
	std::shared_ptr<SDLppTexture> gashamonTexture = std::make_shared<SDLppTexture>(SDLppTexture::FromFile(renderer, "resources/gashamons.png"));

	// On va automatiser l'enregistrement des 20 gashamons via une boucle faisant avancer un rectangle de découpage au fur et à mesure
	// et on va aussi totalement oublier que cette image à la noix (qui m'a coûté 2€) ne peut être découpée de cette façon de façon parfaite.

	const unsigned int gashamonX = 4; //< Nombre de Gashasmons en X
	const unsigned int gashamonY = 5; //< Nombre de Gashasmons en Y

	SDL_Rect rect = gashamonTexture->GetRect();
	rect.x = 0;
	rect.y = 0;
	rect.w /= gashamonX;
	rect.h /= gashamonY;

	for (unsigned int y = 0; y < gashamonY; ++y)
	{
		for (unsigned int x = 0; x < gashamonX; ++x)
		{
			std::string name = "G_" + std::to_string(x) + "_" + std::to_string(y); // ex: G_1_2
			
			std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(gashamonTexture, rect); //< Pas de move de la texture car elle servira au prochain tour de boucle
			spriteManager.Register(std::move(name), std::move(sprite)); // On peut move le nom et les sprites car ils ne serviront pas après

			rect.x += rect.w;
		}

		rect.x = 0;
		rect.y += rect.h;
	}
}

void RenderFirstScreen(SDLppFont& font, SDLppRenderer& renderer) {

	SDLppSurface textSurface = font.RenderUTF8Blended("LEFT : Gashadex - RIGHT : Projet S1 - UP : Gashine - DOWN : Fight ! -  ESC : Quitter");
	SDLppTexture textTexture = SDLppTexture::FromSurface(renderer, textSurface);
	SDL_Rect textRect = textTexture.GetRect();
	textRect.x = 200;
	textRect.y = 500;
	renderer.Copy(textTexture, textRect);
	renderer.SetDrawColor(25, 25, 25);
	renderer.Present();
}