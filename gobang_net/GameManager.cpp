#include "GameManager.h"


/********************************

GameManager

********************************/



void GameManager::before() {
	renderMgr = new RenderManager();




	renderMgr->startUp();
}

void GameManager::after() {

	renderMgr->shutDown();
	delete renderMgr;

}
void GameManager::run() {
	before();

	while (!quit) {
		renderMgr->rendEverything();
	}

	after();

}
