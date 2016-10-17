#include "IOManager.h"



void IOManager::startUp() {
	quit = false;

}
void IOManager::shutDown() {
	delete IOManager::get();
}

void IOManager::input(bool &quit) {
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			quit = true;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				mouseLeftDown = true;
				mouseLeftUp = false;
			}
		} else if (e.type == SDL_MOUSEBUTTONUP) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				mouseLeftDown = false;
				mouseLeftUp = true;
			}
		}
	}
}