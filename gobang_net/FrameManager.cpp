#include "FrameManager.h"



void FrameManager::startUp() {

	btnMgr = ButtonManager::get();
	IOMgr = IOManager::get();

	bgnScene = BeginScene::get();
	bgnScene->startUp();

}

void FrameManager::shutDown() {

	delete FrameManager::get();
}

void FrameManager::frame() {
	btnMgr->checkClick(IOMgr->getMouseLeftDown(),IOMgr->getMouseLeftUp());
	
}


