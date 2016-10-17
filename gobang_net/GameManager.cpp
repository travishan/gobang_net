#include "GameManager.h"


/********************************

GameManager

********************************/



void GameManager::before() {
	winMgr = WindowManager::get();
	renderMgr = RenderManager::get();
	ioMgr = IOManager::get();
	frameMgr = FrameManager::get();

	winMgr->startUp();
	renderMgr->startUp();
	ioMgr->startUp();
	frameMgr->startUp();
}

void GameManager::after() {


	frameMgr->shutDown();
	ioMgr->shutDown();
	renderMgr->shutDown();
	winMgr->shutDown();
	

}
void GameManager::run() {
	before();

	while (!quit) {

		ioMgr->input(quit);
		frameMgr->frame();
		renderMgr->rendEverything();
	}

	after();

}
