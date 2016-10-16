#include "GameManager.h"


/********************************

GameManager

********************************/



void GameManager::before() {
	renderMgr = new RenderManager();
	ioMgr = new IOManager();


	renderMgr->startUp();
	ioMgr->startUp();
}

void GameManager::after() {

	renderMgr->shutDown();
	delete renderMgr;

	ioMgr->shutDown();
	delete ioMgr;

}
void GameManager::run() {
	before();

	while (!quit) {

		ioMgr->input(quit);
		renderMgr->rendEverything();
	}

	after();

}
