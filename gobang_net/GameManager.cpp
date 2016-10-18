#include "GameManager.h"


/********************************

GameManager

********************************/



void GameManager::before() {
	winMgr = WindowManager::get();
	btnMgr = ButtonManager::get();
	renderMgr = RenderManager::get();
	ioMgr = IOManager::get();
	frameMgr = FrameManager::get();
	


	winMgr->startUp();
	btnMgr->startUp();
	renderMgr->startUp();
	ioMgr->startUp();
	frameMgr->startUp();
	
}

void GameManager::after() {


	btnMgr->shutDown();
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
		renderMgr->rendEverything(gameState);
	}

	after();

}
