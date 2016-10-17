#include "RenderManager.h"



void RenderManager::startUp() {
	winMgr = WindowManager::get();
	try {
		winMgr->init("gobang");
	} catch (const runtime_error &e) {
		cout << e.what() << endl;
		winMgr->quit();
		return;
	}
	btnMgr = ButtonManager::get();
}

void RenderManager::shutDown() {
	winMgr->quit();
	delete RenderManager::get();
}

void RenderManager::rendEverything() {
	winMgr->clear();

	btnMgr->render();



	winMgr->present();
}