#include "IOManager.h"



void IOManager::startUp() {
	quit = false;

}
void IOManager::shutDown() {

}

void IOManager::input(bool &quit) {
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			quit = true;
		}
	}
}