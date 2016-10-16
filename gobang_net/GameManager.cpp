#include "GameManager.h"


/********************************

GameManager

********************************/



void GameManager::before() {
	renderMgr = RenderManager::get();
	ioMgr = IOManager::get();


	renderMgr->startUp();
	ioMgr->startUp();
}

void GameManager::after() {

	renderMgr->shutDown();
	ioMgr->shutDown();

}
void GameManager::run() {
	before();

	while (!quit) {

		ioMgr->input(quit);
		renderMgr->rendEverything();
	}

	after();

}
