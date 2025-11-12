#include <cstdio>
#include <cstdlib>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include "tree.h"

#define WINDOW_TITLE "trees"
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800

int init(SDL_Window **window, SDL_Renderer **renderer);

int main(void) {
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	if (init(&window, &renderer))
		exit(EXIT_FAILURE);

	Tree tree;

	bool is_running = true;
	SDL_Event e;
	while (is_running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				is_running = false;
				break;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		tree.grow();
		tree.draw(renderer);
		
		SDL_RenderPresent(renderer);

		SDL_Delay(50);
	}

	return EXIT_SUCCESS;
}

int init(SDL_Window **window, SDL_Renderer **renderer) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("%s\n", SDL_GetError());
		return 1;
	}

	*window = SDL_CreateWindow(WINDOW_TITLE,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_RESIZABLE);
	if (*window == nullptr) {
		printf("%s\n", SDL_GetError());
		return 1;
	}

    *renderer = SDL_CreateRenderer(*window, NULL);
    if (*renderer == nullptr) {
		printf("%s", SDL_GetError());
		return 1;
    }
	return 0;
}

