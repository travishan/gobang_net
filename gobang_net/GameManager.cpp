#include "GameManager.h"


/********************************

GameManager

********************************/



void GameManager::before() {
	winMgr = WindowManager::get();
	renderMgr = RenderManager::get();
	ioMgr = IOManager::get();
	sceneMgr = SceneManager::get();
	frameMgr = FrameManager::get();
	


	winMgr->startUp();
	renderMgr->startUp();
	ioMgr->startUp();
	sceneMgr->startUp();
	frameMgr->startUp();
	
}

void GameManager::after() {


	
	frameMgr->shutDown();
	sceneMgr->shutDown();
	ioMgr->shutDown();
	renderMgr->shutDown();
	winMgr->shutDown();
	

}
void GameManager::run() {
	before();

	sceneMgr->push(new BeginScene());
	while (!quit) {

		ioMgr->input(quit);
		frameMgr->frame();
		renderMgr->rendEverything(gameState);
	}

	after();

}
