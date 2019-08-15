#include "SDL.h"
#include "World.h"
#include <stdio.h>
#include "SDL_image.h"

const int SCREEN_W = 640;
const int SCREEN_H = 480;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Renderer* renderer = nullptr;

	World* world = nullptr;

	window = SDL_CreateWindow("Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		world = new World(renderer);
		//Delta time
		Uint64 NOW = SDL_GetPerformanceCounter();
		Uint64 LAST = 0;
		double deltaTime = 0;

		//Gameloop
		bool quit = false;
		while (!quit) {
			//Calculate deltaTime
			LAST = NOW;
			NOW = SDL_GetPerformanceCounter();
			deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

			//Logic
			world->update(deltaTime);

			//Render
			SDL_RenderClear(renderer);
			world->render();

			SDL_RenderPresent(renderer);
		}
	}

	SDL_Delay(3000); // window lasts 3 seconds
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}